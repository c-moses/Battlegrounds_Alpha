modded class MainMenu extends UIScriptedMenu 
{	
	static const string MMip = "95.156.198.237";
	static const int MMport = 11000;
	
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/main_menu.layout");
		
		m_Play						= layoutRoot.FindAnyWidget( "play" );
		m_SettingsButton			= layoutRoot.FindAnyWidget( "settings_button" );
		m_Exit						= layoutRoot.FindAnyWidget( "exit_button" );
	
		m_Mission					= MissionMainMenu.Cast( GetGame().GetMission() );		
		m_LastFocusedButton = 		m_Play;
		m_ScenePC					= m_Mission.GetIntroScenePC();
		
		if( m_ScenePC )
		{
			m_ScenePC.ResetIntroCamera();
		}
		
		m_PlayerName				= TextWidget.Cast( layoutRoot.FindAnyWidget("character_name") );
		
		string version;
		GetGame().GetVersion( version );
		m_Version.SetText( version );
		
		GetGame().GetUIManager().ScreenFadeOut(0);

		SetFocus( null );
		
		Refresh();
		
		GetDayZGame().GetBacklit().MainMenu_OnShow();
	
		g_Game.SetLoadState( DayZLoadState.MAIN_MENU_CONTROLLER_SELECT );
		
		return layoutRoot;
	}
	override bool OnClick( Widget w, int x, int y, int button )
	{
		if( button == MouseState.LEFT )
		{
			if( w == m_Play )
			{
				m_LastFocusedButton = m_Play;
				g_Game.ConnectFromServerBrowser( MMip, MMport, "" ); 
				return true;
			}
			else if ( w == m_SettingsButton )
			{
				OpenSettings();
				return true;
			}
			else if ( w == m_Exit )
			{
				Exit();
				return true;
			}
		}
		return false;
	}

	override void OnChangeCharacter(bool create_character = true)
	{}

	override void LoadMods()
	{
		return;
	}
	
	override void Play()
	{
		return;
	}
}