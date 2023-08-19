class EL_ChangeQuantityButton : SCR_ButtonBaseComponent
{
	[Attribute("", UIWidgets.CheckBox, "True to add quantity, false to reduce.")]
	protected bool m_bIsAdd;
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		bool result = super.OnClick(w, x, y, button);
		
		Print(m_bIsAdd.ToString(), LogLevel.NORMAL);
		
		return result;
	} 
}