class BattlegroundsTeleporters
{
    protected bool m_Inited = false;
    ref array < ref TeleporterLocations > m_TeleLocations;

    void Init()
    {
        m_Inited = true;
        //Print("[BattlegroundsTeleporters] initialized");
        m_TeleLocations = new array<ref TeleporterLocations>;
        InitTeleLocations();
        SpawnTeleporters();
    }

    void InitTeleLocations()
    {
        TeleporterLocations krasno1Teleporter = new TeleporterLocations("11882.700195 140.08 12438.500000", "Nagornoye [J1]");
        krasno1Teleporter.AddDestination("9375.839844 231.872528 14566.256836".ToVector());
        krasno1Teleporter.AddDestination("9390.416016 231.314545 14551.124023".ToVector());
        krasno1Teleporter.AddDestination("9402.541992 231.671600 14568.591797".ToVector());
        m_TeleLocations.Insert(krasno1Teleporter);

        TeleporterLocations krasno2Teleporter = new TeleporterLocations("11881.400391 140.08 12435.799805", "Tisy [A2]");
        krasno2Teleporter.AddDestination("655.604309 493.242126 13553.806641".ToVector());
        krasno2Teleporter.AddDestination("640.133484 494.061829 13565.639648".ToVector());
        krasno2Teleporter.AddDestination("629.432678 493.915192 13551.474609".ToVector());
        m_TeleLocations.Insert(krasno2Teleporter);

        TeleporterLocations krasno3Teleporter = new TeleporterLocations("11880.299805 140.08 12432.900391", "Zaprudnoye [F3]");
        krasno3Teleporter.AddDestination("5244.640137 162.193939 12733.255859".ToVector());
        krasno3Teleporter.AddDestination("5210.769531 161.833267 12733.142578".ToVector());
        krasno3Teleporter.AddDestination("5225.432617 162.491333 12750.355469".ToVector());
        m_TeleLocations.Insert(krasno3Teleporter);

        TeleporterLocations krasno4Teleporter = new TeleporterLocations("11879.099609 140.08 12430.099609", "Sinystok [C4]");
        krasno4Teleporter.AddDestination("2185.567139 240.723923 12222.903320".ToVector());
        krasno4Teleporter.AddDestination("2214.811279 239.687332 12216.146484".ToVector());
        krasno4Teleporter.AddDestination("2208.057129 239.513138 12234.876953".ToVector());
        m_TeleLocations.Insert(krasno4Teleporter);

        TeleporterLocations krasno5Teleporter = new TeleporterLocations("11877.900391 140.08 12427.099609", "Gvozdno [I4]");
        krasno5Teleporter.AddDestination("8121.905273 185.580582 11693.953125".ToVector());
        krasno5Teleporter.AddDestination("8143.340332 184.570572 11705.617188".ToVector());
        krasno5Teleporter.AddDestination("8126.686523 184.074646 11720.229492".ToVector());
        m_TeleLocations.Insert(krasno5Teleporter);

        TeleporterLocations krasno6Teleporter = new TeleporterLocations("11876.700195 140.08 12424.400391", "Grishino [G5]");
        krasno6Teleporter.AddDestination("6069.710449 266.962433 10470.769531".ToVector());
        krasno6Teleporter.AddDestination("6093.287598 267.397186 10458.962891".ToVector());
        krasno6Teleporter.AddDestination("6094.162109 267.050049 10477.411133".ToVector());
        m_TeleLocations.Insert(krasno6Teleporter);

        TeleporterLocations krasno7Teleporter = new TeleporterLocations("11875.500000 140.08 12421.500000", "Lopatino [C6]");
        krasno7Teleporter.AddDestination("2834.375488 274.021973 9923.404297".ToVector());
        krasno7Teleporter.AddDestination("2837.097656 274.053528 9947.684570".ToVector());
        krasno7Teleporter.AddDestination("2854.906494 274.880402 9937.315430".ToVector());
        m_TeleLocations.Insert(krasno7Teleporter);
    }

    TeleporterLocations GetRandomLocation()
    {
        if (m_TeleLocations.Count() > 0)
        {
            int randomIndex = Math.RandomInt(0, m_TeleLocations.Count());
            return m_TeleLocations[randomIndex];
        }
        return null;
    }

    void SpawnTeleporters()
    {
        for (int i = 0; i < m_TeleLocations.Count(); i++)
        {
            TeleporterLocations location = m_TeleLocations[i];
            StaticObj_TeleporterPanel obj = SpawnTele("StaticObj_TeleporterPanel", location.GetPosition(), "113.050000 0.000000 -0.000000".ToVector());
            obj.SetTeleporterLocations(location);
            //Print("[BattlegroundsTeleporters] Teleporters spawned");
        }
    }

    StaticObj_TeleporterPanel SpawnTele(string classname, vector position, vector orientation)
    {
        StaticObj_TeleporterPanel obj = StaticObj_TeleporterPanel.Cast(GetGame().CreateObject(classname, position, false, true));
        obj.SetOrientation(orientation);
        return obj;
    }

    static autoptr BattlegroundsTeleporters g_Instance;
	static autoptr BattlegroundsTeleporters GetInstance()
	{
		if (GetGame().IsServer())
		{
			if (!g_Instance)
			{
				g_Instance = new BattlegroundsTeleporters();
				//Print("[BattlegroundsTeleporters] new instance created");
			}

			return g_Instance;
		}
		else
		{
			//Print("[BattlegroundsTeleporters] attempted to get instance on client side, returning null");
			return null;
		}
	}
}

class TeleporterLocations
{
    vector m_Position;
    string m_Name;
    ref array<vector> m_DestinationCoords;

    void TeleporterLocations(vector position, string name = "")
    {
        m_Position = position;
        m_Name = name;
        m_DestinationCoords = new array<vector>;
        //Print("TeleporterLocations initialized with name: " + name);
    }

    vector GetPosition()
    {
        return m_Position;
    }

    string GetName()
    {
        //Print("GetName: " + m_Name);
        return m_Name;
    }

    void AddDestination(vector dest)
    {
        m_DestinationCoords.Insert(dest);
    }

    vector GetRandomDestination()
    {
        if (m_DestinationCoords.Count() > 0)
        {
            return m_DestinationCoords.Get(Math.RandomInt(0, m_DestinationCoords.Count()));
        }
        return "11870.000000 140.134811 12435.000000".ToVector(); // Krasno, error spawn
    }
}