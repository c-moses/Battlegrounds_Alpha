modded class MissionGameplay extends MissionBase
{
	private ref BattlegroundsWidget m_BattlegroundsWidget;
	private ref CompassWidget m_CompassWidget;

	protected ref LeaderboardWidget m_LeaderboardWidget;
	private float m_LastRPCSentTimestamp = 0;
    private const float RPC_SEND_INTERVAL = 60.0; // seconds

	private ref GPSWidget m_GPSWidget;
	float m_GPSTimer = 0.0;

	override void OnMissionStart()
	{
		super.OnMissionStart();

		GetRPCManager().AddRPC("Battlegrounds", "BattlegroundsSync", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Battlegrounds", "LeaderboardDataSync", this, SingleplayerExecutionType.Client);

		if (!m_BattlegroundsWidget)
		{
			m_BattlegroundsWidget = new BattlegroundsWidget(true);
		}

		if (!m_CompassWidget)
		{
			m_CompassWidget = new CompassWidget(true);
		}

		if (!m_GPSWidget)
		{
			m_GPSWidget = new GPSWidget(true);
		}

		if (!m_LeaderboardWidget)
		{
			m_LeaderboardWidget = LeaderboardWidget.GetInstance();
		}

		//GetGame().GetMission().GetHud().Show(true);
		RequestLeaderboardData();
	}
	
	void RequestLeaderboardData()
    {
        GetRPCManager().SendRPC("Battlegrounds", "LeaderboardSync", new Param, true, null);
    }

	void LeaderboardDataSync(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (type == CallType.Client)
		{
			Param2<array<BGPlayerStats>, string> data;
			if (!ctx.Read(data)) return;

			array<BGPlayerStats> leaderboardData = data.param1;
			string additionalInfo = data.param2;

			/*for (int j = 0; j < leaderboardData.Count(); j++)
			{
				BGPlayerStats player = leaderboardData.Get(j);
				Print("[LeaderboardSync] Rank: " + (j + 1).ToString());
				Print("Player Name: " + player.playerName);
				Print("Player Kills: " + player.playerKills.ToString()); 
				Print("Zombie Kills: " + player.zombieKills.ToString());
				Print("Deaths: " + player.deaths.ToString());
				Print("Cash Earned: " + player.cashEarned.ToString());
				Print("----------------------------------------");
			}*/

			UpdateLeaderboard(leaderboardData);
		}
	}

	void UpdateLeaderboard(array<BGPlayerStats> leaderboardData)
	{
		LeaderboardWidget.GetInstance().UpdateLeaderboardData(leaderboardData);
	}

	void BattlegroundsSync(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		Param3<string, int, float> data;
		if (!ctx.Read(data)) return;

		if (type == CallType.Client)
		{
			UpdateBattlegroundsWidget(data.param1, data.param2, data.param3);
		}
	}

	void UpdateBattlegroundsWidget(string locationName, int playerCount, float progress)
	{
		if (m_BattlegroundsWidget)
		{
			m_BattlegroundsWidget.SetLocation(locationName);
			m_BattlegroundsWidget.SetPlayerCount(playerCount);
			m_BattlegroundsWidget.SetProgress(progress);
		}
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		UAInput locationInput = GetUApi().GetInputByName("UABattlegroundsWidgetToggle");

		if (locationInput && locationInput.LocalPress())
		{
			if (m_BattlegroundsWidget)
			{
				m_BattlegroundsWidget.PanelToggle();
			}
			else
			{
				m_BattlegroundsWidget = new BattlegroundsWidget(true);
			}
		}

		UAInput compassInput = GetUApi().GetInputByName("UACompassToggle");

		if (compassInput && compassInput.LocalPress())
		{
			if (m_CompassWidget)
			{
				m_CompassWidget.CompassToggleHeading();
			}
			else
			{
				m_CompassWidget = new CompassWidget(true);
			}
		}

		UAInput leaderboardInput = GetUApi().GetInputByName("UALeaderboardToggle");

        if (leaderboardInput && leaderboardInput.LocalPress())
        {
            float currentTime = GetGame().GetTime(); // get current time in milliseconds
            if ((currentTime - m_LastRPCSentTimestamp) > RPC_SEND_INTERVAL * 1000)  // convert seconds to milliseconds
            {
                RequestLeaderboardData();
                m_LastRPCSentTimestamp = currentTime;
            }

			LeaderboardWidget.GetInstance().PanelToggle();
        }

		UAInput gpsInput = GetUApi().GetInputByName("UAGPSToggle");

		if (gpsInput && gpsInput.LocalPress())
		{
			if (m_GPSWidget)
			{
				m_GPSWidget.ToggleGPS();
			}
			else
			{
				m_GPSWidget = new GPSWidget(true);
			}
		}

		if (m_GPSWidget && m_GPSWidget.IsGPSVisible())
		{
			m_GPSTimer += timeslice;

			// Check if 5 seconds have elapsed
			if (m_GPSTimer >= 5.0)
			{
				m_GPSWidget.GPSUpdate();
				m_GPSTimer = 0.0;  // Reset the timer
			}
		}
		else
		{
			m_GPSTimer = 0.0;  // Optionally reset the timer when the widget isn't visible
		}
	}

	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		if ((key == KeyCode.KC_W) || (key == KeyCode.KC_A) || (key == KeyCode.KC_S) || (key == KeyCode.KC_D))
		{
			LeaderboardWidget lbWidget = LeaderboardWidget.GetInstance();
			if (lbWidget && lbWidget.IsLBVisible())
			{
				lbWidget.OnHide();
			}
		}
	}

	override void OnPlayerRespawned(Man player)
	{
		PlayerBase playerBase = PlayerBase.Cast(player);
		if (playerBase)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(playerBase.ShowDeadScreen, false, 0);
		}
		
		GetGame().GetSoundScene().SetSoundVolume(g_Game.m_volume_sound,1);
		GetGame().GetSoundScene().SetSpeechExVolume(g_Game.m_volume_speechEX,1);
		GetGame().GetSoundScene().SetMusicVolume(g_Game.m_volume_music,1);
		GetGame().GetSoundScene().SetVOIPVolume(g_Game.m_volume_VOIP,1);
		GetGame().GetSoundScene().SetRadioVolume(g_Game.m_volume_radio,1);

		IngameHud.Cast(GetGame().GetMission().GetHud()).InitBadgesAndNotifiers(); // needed for custom respawns
		GetGame().GetMission().GetHud().Show(true); // needed for custom respawns
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();
		//not used atm
	}
}