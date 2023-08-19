class EL_SelectableListItemButton : SCR_ButtonBaseComponent
{	
	
	protected TextWidget m_wEntityId;
	ref ScriptInvokerInt m_OnButtonSelected = new ScriptInvokerInt();
	
	override void HandlerAttached(Widget w)
	{
		super.HandlerAttached(w);
		
		m_wEntityId = TextWidget.Cast(w.FindAnyWidget("EntityId"));
	}
	
	override void SetToggled(bool toggled, bool animate = true, bool invokeChange = true)
	{
		super.SetToggled(toggled, animate, invokeChange);;
		
		if(toggled){
			m_wBackground.SetColor(Color.Orange);
		}
		
	} 
}