modded class SCR_PlayerController
{
	override void UpdateLocalPlayerController()
	{
		super.UpdateLocalPlayerController();
		
		GetGame().GetInputManager().AddActionListener("EL_Ticketing", EActionTrigger.DOWN, ActionOpenTicketUI);
	}
	
	void ActionOpenTicketUI(float value = 0.0, EActionTrigger trigger = 0)
	{
		EL_TicketUI m_TicketUI = EL_TicketUI.Cast(GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.EL_TicketUI));
	}
}