//This class will handle providing any data required to the m_TicketUI layout

[EntityEditorProps(category: "EL/Ticket")]
class EL_TicketManagerComponentClass : ScriptComponentClass
{
}

class EL_TicketManagerComponent: ScriptComponent
{
	EL_TicketUI m_TicketUI;
	//------------------------------------------------------------------------------------------------
	void OpenTicketUI(float value = 0.0, EActionTrigger trigger = 0)
	{
		m_TicketUI = EL_TicketUI.Cast(GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.EL_TicketUI));
	}
}