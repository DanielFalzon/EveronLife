class EL_OpenTicketAction : ScriptedUserAction
{
	EL_TicketUiManagerComponent m_TicketUiManager;
	
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		m_TicketUiManager.OpenTicketUI();
	}
	
	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		
		m_TicketUiManager = EL_TicketUiManagerComponent.Cast(pOwnerEntity.FindComponent(EL_TicketUiManagerComponent));
	}
	
	//------------------------------------------------------------------------------------------------
    override bool HasLocalEffectOnlyScript()
    {
        return true;
    }
}