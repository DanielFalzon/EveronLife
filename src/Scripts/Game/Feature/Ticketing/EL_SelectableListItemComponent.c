class EL_SelectableListItemComponent : SCR_ButtonBaseComponent
{	
	protected int m_iEntityId;
	
	//------------------------------------------------------------------------------------------------
	void SetEntityId(int entityId)
	{
		m_iEntityId = entityId;
	}
	
	//------------------------------------------------------------------------------------------------
	int GetEntityId()
	{
		return m_iEntityId;
	}
}