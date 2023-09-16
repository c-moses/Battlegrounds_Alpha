class BattlegroundsEventManager
{
	protected bool m_Inited = false;
	ref array < ref BattlegroundsLocation > m_EventLocations;
	vector m_EventPosition;
	protected string m_CurrentLocationName = "";
	protected string m_LastLocationName = "";
	protected string m_SecondLastLocationName = "";
	protected int m_ZonePlayerCount = 0;
	protected float m_CaptureProgress = 0.0;
	protected float m_UpdateAccumulator = 0.0;
	protected float m_UpdateClientsAccumulator = 0.0;
	const float CAPTURE_TIME = 480.0;
	protected ref array<Object> m_CurrentObjects = new array<Object> ();
	protected ref array<Object> m_LastObjects = new array<Object> ();
    vector m_PreviousEventPosition;
    bool m_PreviousEventPositionSet = false;
    EntityAI m_LastRewardChest;
    vector m_LastRewardChestPosition = "0 0 0";
	protected ref BattlegroundsRewardManager rewardManager;

	void BattlegroundsEventManager()
	{
		//Print("[BattlegroundsEventManager] Constructor called");
		m_EventLocations = new array < ref BattlegroundsLocation > ;
		rewardManager = BattlegroundsRewardManager.GetInstance();
		InitLocations();
	}

	void Init()
	{
		m_Inited = true;
		//Print("[BattlegroundsEventManager] Initialized");
		BGCreateNewEvent();
	}

	void InitLocations()
	{
		m_EventLocations.Insert(new BattlegroundsLocation("4602.107422 339.012451 10671.181641", "East Airstrip (E5)"));
		m_EventLocations.Insert(new BattlegroundsLocation("5229.333496 336.952454 9810.422852", "Airfield Construction (F6)"));
		m_EventLocations.Insert(new BattlegroundsLocation("5333.560059 333.539520 8600.181641", "Kabanino (F7)"));
		m_EventLocations.Insert(new BattlegroundsLocation("4548.047363 317.535614 8314.150391", "Vybor Military (E8)"));
		m_EventLocations.Insert(new BattlegroundsLocation("3803.324463 310.907837 8851.864258", "Vybor (D7)"));
		m_EventLocations.Insert(new BattlegroundsLocation("4517.915039 339.012421 9606.736328", "Airfield Main Gate (E6)"));
		m_EventLocations.Insert(new BattlegroundsLocation("4147.739746 339.029083 10536.904297", "West Airstrip (E5)"));
		m_EventLocations.Insert(new BattlegroundsLocation("4036.851318 375.956451 11734.483398", "Bashnya (E4)"));
		m_EventLocations.Insert(new BattlegroundsLocation("3655.222656 192.616440 13097.901367", "Novaya Petrovka (D3)"));
		m_EventLocations.Insert(new BattlegroundsLocation("3524.363281 238.773468 14170.747070", "Road to Tisy (D2)"));
		m_EventLocations.Insert(new BattlegroundsLocation("3679.703857 363.667053 14817.707031", "Pobeda (D1)"));
		m_EventLocations.Insert(new BattlegroundsLocation("2588.966797 448.012970 14839.582031", "Tisy Lodge (C1)"));
		m_EventLocations.Insert(new BattlegroundsLocation("1929.205322 434.543671 14868.490234", "Tisy Ponds (B1)"));
		m_EventLocations.Insert(new BattlegroundsLocation("1720.422729 451.742401 14289.727539", "Tisy Main Gate (B2)"));
		m_EventLocations.Insert(new BattlegroundsLocation("1821.976929 434.447205 13801.406250", "Tisy Helipads (B2)"));
		m_EventLocations.Insert(new BattlegroundsLocation("1519.818359 439.022400 13594.524414", "Tisy Tents (B2)"));
		m_EventLocations.Insert(new BattlegroundsLocation("4800.718750 474.788727 15076.881836", "West Stary (E1)"));
		m_EventLocations.Insert(new BattlegroundsLocation("5810.128906 474.212463 15185.634766", "Stary Sawmill (F1)"));
		m_EventLocations.Insert(new BattlegroundsLocation("6716.039551 377.162445 14504.408203", "Kamensk (G1)"));
		m_EventLocations.Insert(new BattlegroundsLocation("7860.437500 343.528351 14697.297852", "Troitskoye (H1)"));
		m_EventLocations.Insert(new BattlegroundsLocation("8456.152344 205.371796 13950.531250", "Arsenovo (I2)"));
		m_EventLocations.Insert(new BattlegroundsLocation("8167.087891 112.355873 12746.282227", "East Severograd (I3)"));
		m_EventLocations.Insert(new BattlegroundsLocation("7741.463379 118.334648 12654.988281", "West Severograd (H3)"));
		m_EventLocations.Insert(new BattlegroundsLocation("7515.248535 216.053680 13575.814453", "Kalinovka (H2)"));
	}

    BattlegroundsLocation GetRandomLocation()
    {
        if (m_EventLocations.Count() > 0)
        {
            ref array<int> validIndexes = new array<int>;

            for (int i = 0; i < m_EventLocations.Count(); i++)
            {
                vector potentialLocation = m_EventLocations[i].GetPosition();

                if (m_PreviousEventPositionSet)
                {
                    float distance = vector.Distance(m_PreviousEventPosition, potentialLocation);
                    if (distance <= 1500)
                    {
                        //Print("[BattlegroundsEventManager] Potential location (" + m_EventLocations[i].GetName() + ") coords: " + potentialLocation.ToString() + " is within 1500m with a distance of " + distance.ToString());
                        validIndexes.Insert(i);
                    }
                    else
                    {
                        //Print("[BattlegroundsEventManager] Potential location (" + m_EventLocations[i].GetName() + ") coords: " + potentialLocation.ToString() + " is outside 1500m with a distance of " + distance.ToString());
                    }
                }
            }

            if (validIndexes.Count() == 0)
            {
                //Print("[BattlegroundsEventManager] No locations within 1500m");
                for (int j = 0; j < m_EventLocations.Count(); j++)
                {
                    validIndexes.Insert(j);
                }
            }

            int safetyCounter = 0;
            int randomIndex;
            BattlegroundsLocation randomLocation;

            randomIndex = validIndexes[Math.RandomInt(0, validIndexes.Count())];
            randomLocation = m_EventLocations[randomIndex];

            while ((randomLocation.GetName() == m_CurrentLocationName || randomLocation.GetName() == m_LastLocationName || randomLocation.GetName() == m_SecondLastLocationName) && safetyCounter < 100)
            {
                //Print("[BattlegroundsEventManager] Event location '" + randomLocation.GetName() + "' is not suitable - continue searching...");
                randomIndex = validIndexes[Math.RandomInt(0, validIndexes.Count())];
                randomLocation = m_EventLocations[randomIndex];
                safetyCounter++;
            }

            if (safetyCounter == 100)
            {
                //Print("[BattlegroundsEventManager] Safety counter limit reached - choosing a random location from the valid ones");
                randomIndex = validIndexes[Math.RandomInt(0, validIndexes.Count())];
                randomLocation = m_EventLocations[randomIndex];
            }

            //Print("[BattlegroundsEventManager] Event location chosen: " + randomLocation.GetName());
            return randomLocation;
        }

        //Print("[BattlegroundsEventManager] No event locations available");
        return null;
    }

    void BGCreateNewEvent()
	{
		BattlegroundsLocation location = GetRandomLocation();
		if (location)
		{
			m_SecondLastLocationName = m_LastLocationName;
			m_LastLocationName = m_CurrentLocationName;

			m_EventPosition = location.GetPosition();
			m_CurrentLocationName = location.GetName();

			Print("[BattlegroundsEventManager] New Event: " + m_CurrentLocationName);

			Object greenSmoke = GetGame().CreateObject("BGSmokeGreen", m_EventPosition);
			m_EventPosition = greenSmoke.GetPosition();
			m_CurrentObjects.Insert(greenSmoke);

			float distance = 100.0;

			array<vector> directions = { "0 0 1",	// North
				"0.707 0 0.707",	// NE
				"1 0 0",	// East
				"0.707 0 -0.707",	// SE
				"0 0 -1",	// South
				"-0.707 0 -0.707",	// SW
				"-1 0 0",	// West
				"-0.707 0 0.707"	// NW
			};

			for (int i = 0; i < directions.Count(); i++)
			{
				vector redSmokePos = m_EventPosition + (directions[i] *distance);
				Object redSmoke = GetGame().CreateObject("BGSmokeRed", redSmokePos);
				m_CurrentObjects.Insert(redSmoke);
			}

			m_CaptureProgress = 0.0;
			SendUpdateToClients();
		}
	}

    void RewardPlayersNearEvent()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        string currencyClass = "TraderPlus_Money_Dollar1";
        CurrencyHelper helper = new CurrencyHelper();

        for (int i = 0; i < players.Count(); i++)
        {
            PlayerBase player = PlayerBase.Cast(players[i]);
            if (player)
            {
                float distanceToZoneCenter = vector.Distance(player.GetPosition(), m_EventPosition);
                int currencyAmount;

                if (distanceToZoneCenter <= 100)
                {
                    currencyAmount = 100;
                }
                else if (distanceToZoneCenter > 100 && distanceToZoneCenter <= 200)
                {
                    currencyAmount = 50;
                }
                else if (distanceToZoneCenter > 200 && distanceToZoneCenter <= 300)
                {
                    currencyAmount = 20;
                }
                else
                {
                    continue;
                }

                helper.AddCurrencyStackToPlayer(player, currencyClass, currencyAmount);
				rewardManager.UpdatePlayerStat(player, "cashEarned", currencyAmount);
            }
        }
    }

	void OnCaptureReached()
	{
        if (m_EventPosition != "0 0 0") 
        {
            m_PreviousEventPosition = m_EventPosition;
            m_PreviousEventPositionSet = true;
            //Print("[BattlegroundsEventManager] Saved coords from last event: " + m_PreviousEventPosition );
        }

		if (m_LastObjects.Count() > 0)
		{
			DeleteObjects(m_LastObjects);
			//Print("[BattlegroundsEventManager] Deleted objects from last event");
		}

		else
		{
			//Print("[BattlegroundsEventManager] No last objects found to delete");
		}

		m_LastLocationName = m_CurrentLocationName;
		m_LastObjects.Copy(m_CurrentObjects);

		m_CurrentLocationName = "";
		m_CurrentObjects.Clear();
		//Print("[BattlegroundsEventManager] Cleared current objects array");

		BGSpawnRewards();
		BGCreateNewEvent();
	}

    void BGSpawnRewards()
    {
        if (m_LastRewardChest)
        {
            GetGame().ObjectDelete(m_LastRewardChest);
            m_LastRewardChest = null;
            m_LastRewardChestPosition = "0 0 0";
            //Print("[BattlegroundsEventManager] Deleted rewards from last event");
        }

        if (m_EventPosition != "0 0 0")
        {
            Object obj = GetGame().CreateObject("BattlegroundsRewardCrate", m_EventPosition);
            m_LastRewardChest = EntityAI.Cast(obj);
            
            if (m_LastRewardChest)
            {
                m_LastRewardChestPosition = m_EventPosition;
                BattlegroundsLootManager.AddRewardLoot(m_LastRewardChest);
                //Print("[BattlegroundsEventManager] Reward crate spawned at: " + m_EventPosition.ToString());
            }
        }
        else
        {
            //Print("[BattlegroundsEventManager] Error: m_EventPosition is invalid. Cannot spawn Reward Chest.");
        }
    }

    void DeleteObjects(array<Object> objects)
	{
		for (int i = 0; i < objects.Count(); i++)
		{
			GetGame().ObjectDelete(objects[i]);
		}

		objects.Clear();
	}

	void SendUpdateToClients()
	{
		ref array<Man> players = new array<Man> ;
		GetGame().GetPlayers(players);

		foreach(Man player: players)
		{
			PlayerBase pb = PlayerBase.Cast(player);
			if (pb)
			{
				ref Param3<string, int, float> data = new Param3<string, int, float> (m_CurrentLocationName, m_ZonePlayerCount, m_CaptureProgress);
				GetRPCManager().SendRPC("Battlegrounds", "BattlegroundsSync", data, true, pb.GetIdentity());
			}
		}
	}

    int CountPlayersNearEvent(float radius)
	{
		array<Man> players = new array<Man> ;
		GetGame().GetPlayers(players);

		int count = 0;
		for (int i = 0; i < players.Count(); i++)
		{
			Man player = players[i];
			if (vector.Distance(player.GetPosition(), m_EventPosition) <= radius)
			{
				count++;
			}
		}

		return count;
	}

	vector GetEventPosition()
	{
		return m_EventPosition;
	}

    void OnUpdate(float timeslice)
	{
        if (!GetGame())
        {
            return;
        }

		if (!m_Inited)
		{
			return;
		}

		m_UpdateAccumulator += timeslice;
		m_UpdateClientsAccumulator += timeslice;

		if (m_UpdateClientsAccumulator >= 10.0)
		{
			SendUpdateToClients();
			RewardPlayersNearEvent();
			m_UpdateClientsAccumulator = 0.0;
		}

		float progressIncrement = 100.0 / CAPTURE_TIME;

		if (m_UpdateAccumulator >= 1.0)
		{
			int zonePlayerCount = CountPlayersNearEvent(300);

			if (zonePlayerCount > 0)
			{
				if (m_CaptureProgress < 100.0)
				{
					m_CaptureProgress += progressIncrement;

					if (m_CaptureProgress > 100.0)
					{
						m_CaptureProgress = 100.0;
					}

					SendUpdateToClients();
					//Print("[BattlegroundsEventManager] Capture Progress: " + m_CaptureProgress);

					if (m_CaptureProgress == 100.0)
					{
						OnCaptureReached();
					}
				}
			}
			else
			{
				if (m_CaptureProgress > 0.0)
				{
					m_CaptureProgress -= progressIncrement;
					if (m_CaptureProgress < 0.0)
					{
						m_CaptureProgress = 0.0;
					}

					SendUpdateToClients();
					//Print("[BattlegroundsEventManager] Capture Progress: " + m_CaptureProgress);
				}
			}

			if (zonePlayerCount != m_ZonePlayerCount)
			{
				m_ZonePlayerCount = zonePlayerCount;
				SendUpdateToClients();
				//Print("[BattlegroundsEventManager] Current Players in zone: " + zonePlayerCount);
			}

			m_UpdateAccumulator = 0.0;
		}
	}

	static autoptr BattlegroundsEventManager g_Instance;
	static autoptr BattlegroundsEventManager GetInstance()
	{
		if (GetGame().IsServer())
		{
			if (!g_Instance)
			{
				g_Instance = new BattlegroundsEventManager();
				//Print("[BattlegroundsEventManager] New instance created");
			}

			return g_Instance;
		}
		else
		{
			//Print("[BattlegroundsEventManager] Attempted to get instance on client side, returning null");
			return null;
		}
	}
}