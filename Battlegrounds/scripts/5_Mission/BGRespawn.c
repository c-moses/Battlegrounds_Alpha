modded class RespawnDialogue : UIScriptedMenu
{
	const int 					ID_LOADOUT1 = 101;
	const int 					ID_LOADOUT2 = 102;
    const int 					ID_LOADOUT3 = 103;
	const int 					ID_LOADOUT4 = 104;
    const int 					ID_LOADOUT5 = 105;
	const int 					ID_LOADOUT6 = 106;
	const int 					ID_LOADOUT7 = 107;
	const int 					ID_LOADOUT8 = 108;
	const int 					ID_LOADOUT9 = 109;
    const int 					ID_LOADOUT10 = 110;
	const int 					ID_LOADOUT11 = 111;
	const int 					ID_LOADOUT12 = 112;
	 
	Widget 						m_Loadout1;
    Widget						m_Loadout2;
	Widget						m_Loadout3;
    Widget						m_Loadout4;
	Widget						m_Loadout5;
    Widget						m_Loadout6;
	Widget						m_Loadout7;
	Widget						m_Loadout8;
    Widget						m_Loadout9;
	Widget						m_Loadout10;
    Widget						m_Loadout11;
	Widget						m_Loadout12;

	TextWidget					m_CivilianWidget;
	TextWidget					m_HunterWidget;
	TextWidget					m_SoldierWidget;
	TextWidget					m_TeamsWidget;
	
	Widget 						m_CurrentlyHighlighted;
	
	void RespawnDialogue();
	void ~RespawnDialogue();
	
	override Widget Init()
	{
		layoutRoot 			= GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/RespawnDialogue.layout");
		m_CivilianWidget	= TextWidget.Cast(layoutRoot.FindAnyWidget("civilian_widget"));
		m_HunterWidget		= TextWidget.Cast(layoutRoot.FindAnyWidget("hunter_widget"));
		m_SoldierWidget		= TextWidget.Cast(layoutRoot.FindAnyWidget("soldier_widget"));
		m_TeamsWidget		= TextWidget.Cast(layoutRoot.FindAnyWidget("teams_widget"));
		m_Loadout1 			= layoutRoot.FindAnyWidget("respawn_button_civilian1");
        m_Loadout2 			= layoutRoot.FindAnyWidget("respawn_button_civilian2");
        m_Loadout3 			= layoutRoot.FindAnyWidget("respawn_button_civilian3");
        m_Loadout4 			= layoutRoot.FindAnyWidget("respawn_button_hunter1");
        m_Loadout5 			= layoutRoot.FindAnyWidget("respawn_button_hunter2");
        m_Loadout6			= layoutRoot.FindAnyWidget("respawn_button_hunter3");
		m_Loadout7			= layoutRoot.FindAnyWidget("respawn_button_soldier1");
		m_Loadout8 			= layoutRoot.FindAnyWidget("respawn_button_soldier2");
        m_Loadout9 			= layoutRoot.FindAnyWidget("respawn_button_soldier3");
        m_Loadout10 		= layoutRoot.FindAnyWidget("respawn_button_teams1");
        m_Loadout11			= layoutRoot.FindAnyWidget("respawn_button_teams2");
		m_Loadout12			= layoutRoot.FindAnyWidget("respawn_button_teams3");

		return layoutRoot;
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (GetUApi().GetInputByID(UAUIBack).LocalPress() || GetUApi().GetInputByID(UAUIMenu).LocalPress())
			Close();
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		switch (w.GetUserID())
		{
			case IDC_CANCEL:
				Close();
				Print("Loadout Select Menu: Cancel");
				return true;

			case ID_LOADOUT1:
				Print("Loadout Select Menu: Loadout 1");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(101));
				return RequestRespawn(true);

			case ID_LOADOUT2:
				Print("Loadout Select Menu: Loadout 2");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(102));
				return RequestRespawn(true);
            
            case ID_LOADOUT3:
				Print("Loadout Select Menu: Loadout 3");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(103));
				return RequestRespawn(true);

			case ID_LOADOUT4:
				Print("Loadout Select Menu: Loadout 4");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(104));
				return RequestRespawn(true);

            case ID_LOADOUT5:
				Print("Loadout Select Menu: Loadout 5");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(105));
				return RequestRespawn(true);

			case ID_LOADOUT6:
				Print("Loadout Select Menu: Loadout 6");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(106));
				return RequestRespawn(true);

			case ID_LOADOUT7:
				Print("Loadout Select Menu: Loadout 7");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(107));
				return RequestRespawn(true);

			case ID_LOADOUT8:
				Print("Loadout Select Menu: Loadout 8");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(108));
				return RequestRespawn(true);

			case ID_LOADOUT9:
				Print("Loadout Select Menu: Loadout 9");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(109));
				return RequestRespawn(true);

            case ID_LOADOUT10:
				Print("Loadout Select Menu: Loadout 10");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(110));
				return RequestRespawn(true);

			case ID_LOADOUT11:
				Print("Loadout Select Menu: Loadout 11");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(111));
				return RequestRespawn(true);

			case ID_LOADOUT12:
				Print("Loadout Select Menu: Loadout 12");
				GetRPCManager().SendRPC("LoadoutSelect", "RespawnMode", new Param1<int>(112));
				return RequestRespawn(true);
		}

		return false;
	}

	override bool RequestRespawn(bool random)
	{
		IngameHud.Cast(GetGame().GetMission().GetHud()).InitBadgesAndNotifiers();
		Man player = GetGame().GetPlayer();
		if (player && (player.GetPlayerState() == EPlayerStates.ALIVE && !player.IsUnconscious()))
			return false;
		
		#ifdef PLATFORM_CONSOLE
		InGameMenuXbox menu_ingame = InGameMenuXbox.Cast(GetGame().GetUIManager().FindMenu(MENU_INGAME));
		#else
		InGameMenu menu_ingame = InGameMenu.Cast(GetGame().GetUIManager().FindMenu(MENU_INGAME));
		#endif
		
		if (!menu_ingame)
			return false;
		
		menu_ingame.MenuRequestRespawn(this, random);
		return true;
	}
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		ColorHighlight(w);
		return false;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		ColorNormal(w);
		return true;
	}
	
	override void OnShow()
	{
		super.OnShow();
	}
	
	override bool OnFocus(Widget w, int x, int y)
	{
		if (IsFocusable(w))
		{
			ColorHighlight(w);
		}
		return false;
	}
	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		if (IsFocusable(w))
		{
			ColorNormal(w);
			return true;
		}

		return false;
	}
	
	override bool IsFocusable(Widget w)
	{
		if (w)
		{
			if (w.GetUserID() == IDC_CANCEL || w.GetUserID() == ID_LOADOUT1 || w.GetUserID() == ID_LOADOUT2 || w.GetUserID() == ID_LOADOUT3 || w.GetUserID() == ID_LOADOUT4 || w.GetUserID() == ID_LOADOUT5 || w.GetUserID() == ID_LOADOUT6 || w.GetUserID() == ID_LOADOUT7 || w.GetUserID() == ID_LOADOUT8 || w.GetUserID() == ID_LOADOUT9 || w.GetUserID() == ID_LOADOUT10 || w.GetUserID() == ID_LOADOUT11 || w.GetUserID() == ID_LOADOUT12 );
				return true;
		}

		return false;
	}
	
	protected override void ColorHighlight(Widget w)
	{
		if (!w)
			return;

		if (m_CurrentlyHighlighted != w)
		{
			if (m_CurrentlyHighlighted)
				ColorNormal(m_CurrentlyHighlighted);

			m_CurrentlyHighlighted = w;
		}

		ButtonSetColor(w, ARGB(255, 0, 0, 0));
		ButtonSetTextColor(w, ARGB(255, 255, 0, 0));
	}
	
	protected override void ColorNormal(Widget w)
	{
		if (!w)
			return;
		
		ButtonSetColor(w, ARGB(0, 0, 0, 0));
		ButtonSetTextColor(w, ARGB(255, 255, 255, 255));
	}
	
	protected override void ButtonSetColor(Widget w, int color)
	{
		Widget panel = w.FindWidget(w.GetName() + "_panel");
		if (panel)
			panel.SetColor(color);
	}
	
	protected override void ButtonSetTextColor(Widget w, int color)
	{
		TextWidget label = TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_label"));
		if (label)
			label.SetColor(color);
	}
}

