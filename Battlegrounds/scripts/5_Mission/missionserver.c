modded class MissionServer
{
    protected ref BattlegroundsConfig m_Config;
    private ref map<string, int> m_SelectedLoadouts = new map<string, int> ();

    void MissionServer()
    {
        if(!BattlegroundsConfigLoader.LoadConfig("Battlegrounds.json", m_Config))
        {
            //Print("[MissionServer] Error: Failed to load Battlegrounds.json");
            return;
        }
        
        GetDayZGame().SetBattlegroundsConfig(m_Config);
        GetDayZGame().SetBGPlayerStatsMap(m_Config);
    }
    
    override void OnInit()
    {
        super.OnInit();

        GetRPCManager().AddRPC("Battlegrounds", "LeaderboardSync", this, SingleplayerExecutionType.Both);
        GetRPCManager().AddRPC("LoadoutSelect", "RespawnMode", this, SingleplayerExecutionType.Server);

        if (GetGame())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.InitBattlegrounds, 3000, false);
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.InitTeleporters, 5000, false);
        }
    }

    void InitBattlegrounds()
    {
        if (GetGame())
        {
            BattlegroundsEventManager.GetInstance().Init();

            // Initialize BGLeaderboardManager
            if (m_Config && m_Config.Players)
            {
                BGLeaderboardManager.GetInstance(m_Config.Players);
            }
        }
    }

	void InitTeleporters()
    {
        if (GetGame())
        {
            BattlegroundsTeleporters.GetInstance().Init();
        }
    }

    override void OnUpdate(float timeslice)
    {
        if (GetGame())
        {
            BattlegroundsEventManager.GetInstance().OnUpdate(timeslice);
            super.OnUpdate(timeslice);
        }
    }

	void RespawnMode(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		{
			if (type != CallType.Server)
				return;

			Param1<int> data;
			if (!ctx.Read(data))
				return;

			if (sender == null)
				return;

			int clientResponse = data.param1;
			m_SelectedLoadouts.Set(sender.GetId(), clientResponse);

			//Print("MissionServer RPC recieved: selected loadout " + clientResponse);
		}
	}

	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		string characterType;

		if (ProcessLoginData(ctx) && (m_RespawnMode == GameConstants.RESPAWN_MODE_CUSTOM))
		{
			characterType = GetGame().CreateRandomPlayer();
		}
		else // disabled respawn dialogue
		{
			int randomLoadout = Math.RandomInt(101, 106);  // 101 to 105
			m_SelectedLoadouts.Set(identity.GetId(), randomLoadout);

			characterType = GetGame().CreateRandomPlayer();
		}

		int selectedLoadout = m_SelectedLoadouts.Get(identity.GetId());
		vector customSpawnPos = TeamSpawnPoints.GetSpawnForTeam(GetTeamForLoadout(selectedLoadout));

		if (CreateCharacter(identity, customSpawnPos, ctx, characterType))
		{
			ApplyLoadout(m_player, selectedLoadout);
		}

		return m_player;
	}

	string GetTeamForLoadout(int selectedLoadout)
	{
		switch (selectedLoadout)
		{
			case 101:
			case 102:
			case 103:
				return "white";
			case 104:
			case 105:
			case 106:
				return "blue";
			case 107:
			case 108:
			case 109:
				return "red";
			case 110:
			case 111:
			case 112:
				return "green";
			default:
				return "white";
		}
		return "white"; // do not remove (compiler error, idk)
	}

	PlayerBase ApplyLoadout(PlayerBase playerInstance, int selectedLoadout)
	{
		string team = GetTeamForLoadout(selectedLoadout);
		vector spawnPos = TeamSpawnPoints.GetSpawnForTeam(team);
		//Print("Determined Team: " + team);

	switch (selectedLoadout)
	{
		case 101:
			Loadout1(playerInstance);
			break;
		case 102:
			Loadout2(playerInstance);
			break;
		case 103:
			Loadout3(playerInstance);
			break;
		case 104:
			Loadout4(playerInstance);
			break;
		case 105:
			Loadout5(playerInstance);
			break;
		case 106:
			Loadout6(playerInstance);
			break;
		case 107:
			Loadout7(playerInstance);
			break;
		case 108:
			Loadout8(playerInstance);
			break;
		case 109:
			Loadout9(playerInstance);
			break;
		case 110:
			Loadout10(playerInstance);
			break;
		case 111:
			Loadout11(playerInstance);
			break;
		case 112:
			Loadout12(playerInstance);
			break;
		default:
			int randomLoadoutChoice = Math.RandomInt(101, 106); //  101 to 105
			switch (randomLoadoutChoice)
			{
				case 101:
					Loadout1(playerInstance);
					break;
				case 102:
					Loadout2(playerInstance);
					break;
				case 103:
					Loadout3(playerInstance);
					break;
				case 104:
					Loadout4(playerInstance);
					break;
				case 105:
					Loadout5(playerInstance);
					break;
			}
			break;
	}

		playerInstance.SetPosition(spawnPos);

		//Print("Spawn Position: " + spawnPos.ToString());
		//Print("Player Set Position: " + playerInstance.GetPosition().ToString());

		return playerInstance;
	}

	//civilian
	static void Loadout1(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("M65Jacket_Black");
		player.GetInventory().CreateInInventory("CargoPants_Black");
		AddGeneralItems(player);
	}

	static void Loadout2(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("QuiltedJacket_Green");
		player.GetInventory().CreateInInventory("Jeans_Green");
		AddGeneralItems(player);
	}

	static void Loadout3(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("WoolCoat_BrownCheck");
		player.GetInventory().CreateInInventory("Jeans_Black");
		AddGeneralItems(player);
	}

	//hunter
	static void Loadout4(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("HuntingJacket_Brown");
		player.GetInventory().CreateInInventory("HunterPants_Brown");
		AddGeneralItems(player);
	}

	static void Loadout5(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("HuntingJacket_Spring");
		player.GetInventory().CreateInInventory("HunterPants_Spring");
		AddGeneralItems(player);
	}

	static void Loadout6(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("HuntingJacket_Summer");
		player.GetInventory().CreateInInventory("HunterPants_Summer");
		AddGeneralItems(player);
	}

	//soldier
	static void Loadout7(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("BDUJacket");
		player.GetInventory().CreateInInventory("BDUPants");
		AddGeneralItems(player);
	}

	static void Loadout8(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("USMCJacket_Woodland");
		player.GetInventory().CreateInInventory("USMCPants_Woodland");
		AddGeneralItems(player);
	}

	static void Loadout9(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("TTsKOJacket_Camo");
		player.GetInventory().CreateInInventory("TTSKOPants");
		AddGeneralItems(player);
	}

	//teams
	static void Loadout10(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("MVS_CombatShirt_BlueTeam");
		player.GetInventory().CreateInInventory("MVS_CombatPants_BlueTeam");
		AddGeneralItems(player);
	}

	static void Loadout11(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("MVS_CombatShirt_RedTeam");
		player.GetInventory().CreateInInventory("MVS_CombatPants_RedTeam");
		AddGeneralItems(player);
	}

	static void Loadout12(PlayerBase player)
	{
		EntityAI itemEnt;
		AddPlayerStats(player);
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
		player.GetInventory().CreateInInventory("MVS_CombatShirt_GreenTeam");
		player.GetInventory().CreateInInventory("MVS_CombatPants_GreenTeam");
		AddGeneralItems(player);
	}

	static void AddPlayerStats(PlayerBase player)
	{
		player.GetStatWater().Add(3400);
		player.GetStatEnergy().Add(3400);
	}

	static void EquipAK74(PlayerBase player)
	{
		EntityAI itemEnt = player.GetInventory().CreateInInventory("AKS74U");
		itemEnt.GetInventory().CreateInInventory("Rev_AK_Bttstck");

		AKS74U ak74Instance = AKS74U.Cast(itemEnt);
		if (ak74Instance)
		{
			ak74Instance.SpawnAttachedMagazine("Mag_AK74_30Rnd");
		}

		player.SetQuickBarEntityShortcut(ak74Instance, 1, true); // Set AK to slot 2
	}

	static void EquipNVG(PlayerBase player)
	{
		EntityAI itemEnt = CreateItemInInventory(player, "NVGHeadstrap");
		ItemBase nvg = ItemBase.Cast(CreateItemInEntity(itemEnt, "NVGoggles"));
		if (nvg)
		{
			CreateItemInEntity(nvg, "Battery9V");
		}
	}

	static void EquipBelt(PlayerBase player)
	{
    	EntityAI beltEnt = player.GetInventory().CreateInInventory("MilitaryBelt");

    	EntityAI bandage1 = beltEnt.GetInventory().CreateAttachment("BandageDressing");
    	player.SetQuickBarEntityShortcut(bandage1, 2, true);  // Set Bandage to slot 3

    	EntityAI knife = beltEnt.GetInventory().CreateAttachment("CombatKnife");
    	player.SetQuickBarEntityShortcut(knife, 3, true);  // Set Knife to slot 4

    	EntityAI mapInst = beltEnt.GetInventory().CreateAttachment("ChernarusMap");
    	player.SetQuickBarEntityShortcut(mapInst, 4, true);  // Set Map to slot 5

    	EntityAI radio = beltEnt.GetInventory().CreateAttachment("PersonalRadio");
    	if (radio)
    	{
        	radio.GetInventory().CreateInInventory("Battery9V");
        	player.SetQuickBarEntityShortcut(radio, 5, true);  // Set Radio to slot 6
    	}
	}

	static void AddGeneralItems(PlayerBase player)
	{
		int i;
		EntityAI itemEnt;

		player.GetInventory().CreateInInventory("CmsKit");
		CreateMultipleItems(player, "BloodBagIV", 2);
		CreateMultipleItems(player, "Ammo_545x39", 4);
		player.GetInventory().CreateInInventory("TraderPlus_Money_DIM_Gold");
		CreateMultipleItems(player, "Mag_AK74_30Rnd", 6);
		player.GetInventory().CreateInInventory("WoolGlovesFingerless_Black");
		player.GetInventory().CreateInInventory("MilitaryBoots_Black");
	}

	static EntityAI CreateItemInInventory(PlayerBase player, string itemName)
	{
		return player.GetInventory().CreateInInventory(itemName);
	}

	static EntityAI CreateItemInEntity(EntityAI entity, string itemName)
	{
		return entity.GetInventory().CreateInInventory(itemName);
	}

	static void CreateMultipleItems(PlayerBase player, string itemName, int count)
	{
		for (int i = 0; i < count; i++)
		{
			player.GetInventory().CreateInInventory(itemName);
		}
	}

    void LeaderboardSync(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            BGLeaderboardManager manager = BGLeaderboardManager.GetInstance();

            if (manager)
            {
                // Sort players based on cashEarned
                manager.QuickSortByCashEarned(0, m_Config.Players.Count() - 1);

                array<BGPlayerStats> sortedPlayers = manager.GetSortedList("desc");

                // Now, you can fetch top 50 players
                array<BGPlayerStats> top50Players = new array<BGPlayerStats>();
                for (int i = 0; i < sortedPlayers.Count() && i < 50; i++)
                {
                    top50Players.Insert(sortedPlayers.Get(i));
                }

                Param2<array<BGPlayerStats>, string> data = new Param2<array<BGPlayerStats>, string>(top50Players, "additional info");

                GetRPCManager().SendRPC("Battlegrounds", "LeaderboardDataSync", data, true, sender);

                /*for (int j = 0; j < top50Players.Count(); j++)
                {
                    BGPlayerStats player = top50Players.Get(j);
                    Print("[LeaderboardSync] Rank: " + (j + 1).ToString());
                    Print("Player Name: " + player.playerName);
                    Print("Player Kills: " + player.playerKills.ToString());
                    Print("Zombie Kills: " + player.zombieKills.ToString());
                    Print("Deaths: " + player.deaths.ToString());
                    Print("Cash Earned: " + player.cashEarned.ToString());
                    Print("----------------------------------------");
                }*/
            }
            else
            {
                //Print("[LeaderboardSync] No player data found in the loaded configuration or BGLeaderboardManager not initialized.");
            }
        }
    }
};

class TeamSpawnPoints 
{
	const static ref array<vector> whiteTeam = 
	{
		"11870.101563 140.134796 12443.695313".ToVector(),
		"11856.631836 140.134796 12434.152344".ToVector(),
		"11857.794922 140.085999 12428.972656".ToVector()
	}; 

	const static ref array<vector> blueTeam = 
	{
		"11868.767578 140.134811 12440.271484".ToVector(),
		"11870.598633 140.134811 12435.713867".ToVector(),
		"11873.530273 140.134796 12441.328125".ToVector()
	}; 

	const static ref array<vector> redTeam = 
	{
		"11862.409180 140.134796 12425.455078".ToVector(),
		"11863.906250 140.134811 12441.986328".ToVector(),
		"11866.141602 140.134811 12436.391602".ToVector()
	}; 

	const static ref array<vector> greenTeam = 
	{
		"11860.702148 140.134796 12436.655273".ToVector(),
		"11867.421875 140.134796 12429.429688".ToVector(),
		"11865.530273 140.134811 12444.933594".ToVector()
	}; 

	const static ref array<vector> defaultSpawn = 
	{
		"11870.101563 140.134796 12443.695313".ToVector(),
		"11856.631836 140.134796 12434.152344".ToVector(),
		"11857.794922 140.085999 12428.972656".ToVector()
	}; 

	static vector GetSpawnForTeam(string team) 
	{
		switch (team) 
		{
			case "white":
				return whiteTeam.Get(Math.RandomInt(0, whiteTeam.Count() - 1));
			case "blue":
				return blueTeam.Get(Math.RandomInt(0, blueTeam.Count() - 1));
			case "red":
				return redTeam.Get(Math.RandomInt(0, redTeam.Count() - 1));
			case "green":
				return greenTeam.Get(Math.RandomInt(0, greenTeam.Count() - 1));
			default:
				return defaultSpawn.Get(Math.RandomInt(0, defaultSpawn.Count() - 1));
		}

		return defaultSpawn.Get(Math.RandomInt(0, defaultSpawn.Count() - 1)); // do not remove (compiler error, idk)
	}
};

/*
	->	krasno hangar spawns

	const static ref array<vector> whiteTeam = 
	{
		"11870.101563 140.134796 12443.695313".ToVector(),
		"11856.631836 140.134796 12434.152344".ToVector(),
		"11857.794922 140.085999 12428.972656".ToVector()
	}; 

	const static ref array<vector> blueTeam = 
	{
		"11868.767578 140.134811 12440.271484".ToVector(),
		"11870.598633 140.134811 12435.713867".ToVector(),
		"11873.530273 140.134796 12441.328125".ToVector()
	}; 

	const static ref array<vector> redTeam = 
	{
		"11862.409180 140.134796 12425.455078".ToVector(),
		"11863.906250 140.134811 12441.986328".ToVector(),
		"11866.141602 140.134811 12436.391602".ToVector()
	}; 

	const static ref array<vector> greenTeam = 
	{
		"11860.702148 140.134796 12436.655273".ToVector(),
		"11867.421875 140.134796 12429.429688".ToVector(),
		"11865.530273 140.134811 12444.933594".ToVector()
	}; 

		Black armour

		itemEnt = player.GetInventory().CreateInInventory("MVS_Altyn_Black");
		itemEnt.GetInventory().CreateInInventory("MVS_Altyn_Visor_Black");
		itemEnt = player.GetInventory().CreateInInventory("MVS_Combat_Vest_Heavy_Black");
		itemEnt.GetInventory().CreateInInventory("MVS_Heavy_Pouch_Black");

		Green armour

		itemEnt = player.GetInventory().CreateInInventory("MVS_Altyn_OD");
		itemEnt.GetInventory().CreateInInventory("MVS_Altyn_Visor_OD");
		itemEnt = player.GetInventory().CreateInInventory("MVS_Combat_Vest_Heavy_OD");
		itemEnt.GetInventory().CreateInInventory("MVS_Heavy_Pouch_OD");

		Teams armour

		itemEnt = player.GetInventory().CreateInInventory("MVS_Altyn_BlueTeam");
		itemEnt.GetInventory().CreateInInventory("MVS_Altyn_Visor_Black");
		itemEnt = player.GetInventory().CreateInInventory("MVS_Combat_Vest_Heavy_Black");
		itemEnt.GetInventory().CreateInInventory("MVS_Heavy_Pouch_Black");

		itemEnt = player.GetInventory().CreateInInventory("MVS_Altyn_RedTeam");
		itemEnt.GetInventory().CreateInInventory("MVS_Altyn_Visor_Black");
		itemEnt = player.GetInventory().CreateInInventory("MVS_Combat_Vest_Heavy_Black");
		itemEnt.GetInventory().CreateInInventory("MVS_Heavy_Pouch_Black");

		itemEnt = player.GetInventory().CreateInInventory("MVS_Altyn_GreenTeam");
		itemEnt.GetInventory().CreateInInventory("MVS_Altyn_Visor_Black");
		itemEnt = player.GetInventory().CreateInInventory("MVS_Combat_Vest_Heavy_Black");
		itemEnt.GetInventory().CreateInInventory("MVS_Heavy_Pouch_Black");
*/