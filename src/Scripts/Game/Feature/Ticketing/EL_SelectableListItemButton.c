class EL_SelectableListItemButton : SCR_ButtonBaseComponent
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
	
	//------------------------------------------------------------------------------------------------
	override void SetToggled(bool toggled, bool animate = true, bool invokeChange = true)
	{
		super.SetToggled(toggled, animate, invokeChange);;
		
		if(toggled){
			m_wBackground.SetColor(Color.Orange);
		}
		
	} 
}