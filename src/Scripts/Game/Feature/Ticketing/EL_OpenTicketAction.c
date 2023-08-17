class EL_OpenTicketAction : ScriptedUserAction
{
	EL_TicketManagerComponent m_TicketManager;
	
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		m_TicketManager.OpenTicketUI();
	}
	
	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_TicketManager = EL_TicketManagerComponent.Cast(pOwnerEntity.FindComponent(EL_TicketManagerComponent));
	}
}