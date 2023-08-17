//This class will handle any functionalities needed when the player interacts with the menu
class EL_TicketUI : ChimeraMenuBase
{
	//Variables should hold array of players, charges, percentage modifier 
	//Should persist the submission of a charge in order to have re-issue functionality.
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
		Print("OnMenuOpen: ticket dialog opened!", LogLevel.NORMAL);
		
		Widget rootWidget = GetRootWidget();
		
		if (!rootWidget)
		{
			Print("Error in Layout Tutorial layout creation", LogLevel.ERROR);
			return;
		}
	}
}