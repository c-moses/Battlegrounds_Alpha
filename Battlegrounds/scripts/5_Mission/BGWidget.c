class BattlegroundsWidget
{
    protected ref Widget m_Root;
    protected ref Widget m_MainPanel;
    protected ref Widget m_ZonePanel;
    protected ref Widget m_BGPanel;
    protected TextWidget m_Location;
    protected TextWidget m_PlayerCount;
    protected ProgressBarWidget m_ProgressBar;
    protected bool m_PanelVisible;

    void BattlegroundsWidget(bool visible)
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/BattlegroundsWidget.layout");
        m_ZonePanel = m_Root.FindAnyWidget("ZonePanel");
        m_Location = TextWidget.Cast(m_Root.FindAnyWidget("Location"));
        m_PlayerCount = TextWidget.Cast(m_Root.FindAnyWidget("PlayerCount"));
        m_ProgressBar = ProgressBarWidget.Cast(m_Root.FindAnyWidget("ProgressBar"));
        m_PanelVisible = visible;

        ShowHud(m_PanelVisible);
        SetLocation();
        SetPlayerCount();
        SetProgress();
    }

    void ~BattlegroundsWidget()
    {
        m_Root.Unlink();
    }

    void SetLocation(string location = "LOADING")
    {
        if (m_Location)
        {
            m_Location.SetText(location);
        }
    }

    void SetPlayerCount(int count = 0)
    {
        if (m_PlayerCount)
        {
            if (count == 0)
                m_PlayerCount.SetText("");
            else
                m_PlayerCount.SetText(count.ToString() + " Player(s) In Zone");
        }
    }

    void SetProgress(float progress = 0.0)
    {
        if (m_ProgressBar)
        {
            int roundedProgress = Math.Round(progress);
            m_ProgressBar.SetCurrent(roundedProgress);
        }
    }

    void ShowHud(bool show)
    {
        m_ZonePanel.Show(show);
    }

    void PanelSetVisible(bool visible)
    {
        m_PanelVisible = visible;
        ShowHud(m_PanelVisible);
    }

    void PanelToggle()
    {
        m_PanelVisible = !m_PanelVisible;
        ShowHud(m_PanelVisible);
    }
};