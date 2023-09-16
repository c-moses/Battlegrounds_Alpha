modded class InGameMenu
{
	static const string MMpathB = "Battlegrounds/GUI/layouts/IngameMenu.layout";  
	static const string MMdiscord = "discord.gg/4CuTt5pd6e";     
	
	protected Widget m_Discord;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets(MMpathB);
				
		m_ContinueButton	= layoutRoot.FindAnyWidget( "continuebtn" );
		m_ExitButton		= layoutRoot.FindAnyWidget( "exitbtn" );
		m_RestartButton		= layoutRoot.FindAnyWidget( "restartbtn" );
		m_RespawnButton		= layoutRoot.FindAnyWidget( "restartdeadbtn" );
		m_OptionsButton		= layoutRoot.FindAnyWidget( "optionsbtn" );
		m_Discord			= layoutRoot.FindAnyWidget( "discordbtn" );
		
		if (GetGame().IsMultiplayer())
		{
			ButtonSetText(m_RestartButton, "#main_menu_respawn");
		}
		else
		{
			ButtonSetText(m_RestartButton, "#main_menu_restart");
		}
		
		HudShow( false );
		SetGameVersion();
		
		return layoutRoot;
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);
		
		if ( w == m_Discord )
		{
			GetGame().OpenURL(MMdiscord);
			return true;
		}

		return false;
	}
}
