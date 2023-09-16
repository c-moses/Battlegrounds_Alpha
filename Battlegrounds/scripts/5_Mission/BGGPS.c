class GPSWidget extends UIScriptedMenu
{
    private Widget m_Root;
    private Widget m_GPSPanel;
    private TextWidget m_GPSHeader;
    private TextWidget m_GPSTextWidget;

    private bool m_GPSIsVisible;

    void GPSWidget(bool visible)
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/BattlegroundsGPS.layout");
        m_GPSPanel = m_Root.FindAnyWidget("GPSPanel");
        m_GPSHeader = TextWidget.Cast(m_GPSPanel.FindAnyWidget("GPSHeader"));
        m_GPSTextWidget = TextWidget.Cast(m_GPSPanel.FindAnyWidget("GPSText"));

        m_GPSIsVisible = visible;
    }

    void GPSUpdate()
    {
        if (m_GPSIsVisible && m_GPSTextWidget && GetGame().GetPlayer())
        {
            string sector = GetSector();
            m_GPSTextWidget.SetText(sector);
            m_GPSHeader.SetText("You are in:");
        }
    }

    string GetSector()
    {
        DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());
        vector pos = player.GetPosition();
        float x = pos[0];
        float z = pos[2];

        int sectorX = Math.Floor(x / 1000) + 1;

        int mapMaxZ = 15350;
        z = mapMaxZ - z;
        int sectorZ = Math.Floor(z / 1000) + 1;

        array<string> alphabets = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P" };
        string alphabeticX = alphabets[sectorX - 1];

        string numericZ = sectorZ.ToString();

        return "SECTOR " + alphabeticX + numericZ;
    }

    void SetGPSVisible(bool visible)
    {
        m_GPSIsVisible = visible;
    }

    void ToggleGPS()
    {
        m_GPSIsVisible = !m_GPSIsVisible;
        if (m_GPSPanel)
        {
            m_GPSPanel.Show(m_GPSIsVisible);
        }
    }

    bool IsGPSVisible()
    {
        return m_GPSIsVisible;
    }
}