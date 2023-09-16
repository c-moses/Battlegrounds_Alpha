class StaticObj_TeleporterPanel : Building
{
    void Open( int index );
    void InitiateClose( int index );
    void Close( int index );

    ref TeleporterLocations m_TeleporterLocations;

    void StaticObj_TeleporterPanel()
    {}

    void SetTeleporterLocations(TeleporterLocations locations)
    {
        m_TeleporterLocations = locations;
        //Print("SetTeleporterLocations: " + m_TeleporterLocations.GetName());
    }

    vector GetRandomDestination()
    {
        if (m_TeleporterLocations)
        {
            return m_TeleporterLocations.GetRandomDestination();
        }
        return "11870.000000 140.134811 12435.000000"; // Krasno fallback location
    }
};

class ActionTeleport : ActionOpenDoors
{
    protected StaticObj_TeleporterPanel m_Teleporter;

    override string GetText()
    {
        if (m_Teleporter)
        {
            return "Teleport";
        }
        return "Teleport";
    }

    protected bool IsTeleporterPanel(Object target) 
    {
        return target.IsInherited(StaticObj_TeleporterPanel);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (target.GetObject().IsInherited(Building) && !IsTeleporterPanel(target.GetObject()))
            return false;

        if (IsTeleporterPanel(target.GetObject()))
        {
            m_Teleporter = StaticObj_TeleporterPanel.Cast(target.GetObject());
            return true;
        }

        return super.ActionCondition(player, target, item);
    }

    override void OnStartServer(ActionData action_data)
    {
        StaticObj_TeleporterPanel teleporter = StaticObj_TeleporterPanel.Cast(action_data.m_Target.GetObject());
        if (teleporter)
        {
            vector destination = teleporter.GetRandomDestination(); 
            action_data.m_Player.SetPosition(destination);
            teleporter.Close(0);
        }
        else
        {
            super.OnStartServer(action_data);
        }
    }
}

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(ActionTeleport);
	}
};

modded class PlayerBase
{
    override void SetActions(out TInputActionMap InputActionMap)
	{
        super.SetActions(InputActionMap);
		AddAction(ActionTeleport, InputActionMap);
    }
}