modded class SCR_PlayerController
{
	override void UpdateLocalPlayerController()
	{
		super.UpdateLocalPlayerController();
		
		//TODODF: Figure out how to to invoke the event in EL_OpenTicketAction instead.
		GetGame().GetInputManager().AddActionListener("EL_Ticketing", EActionTrigger.DOWN, ActionOpenTicketUI);
	}
	
	void ActionOpenTicketUI(float value = 0.0, EActionTrigger trigger = 0)
	{
		EL_TicketUiMenu m_TicketUiMenu = EL_TicketUiMenu.Cast(GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.EL_TicketUiMenu));
		
		//TODODF: Move over thhe operations for retrieving data here.
	}
}