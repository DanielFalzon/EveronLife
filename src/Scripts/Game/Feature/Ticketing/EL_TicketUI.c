//This class will handle any functionalities needed when the player interacts with the menu
//Look at SCR_PlayerListMenu.CreateEntry
//Look at 

class EL_TicketUI : ChimeraMenuBase
{
	protected  Widget m_wRoot;
	protected VerticalLayoutWidget m_wPlayerList;
	protected VerticalLayoutWidget m_wChargeList;
	
	protected const string LIST_ITEM_LAYOUT = "{482EDF389BB71398}UI/Layouts/WidgetLibrary/EL_SelectableListItem.layout";
	protected const string PLAYERS_CONTAINER_NAME = "PlayerListButtonContainer";
	protected const string CHARGES_CONTAINER_NAME = "ChargeListButtonContainer";
	
	//Variables should hold array of players, charges, percentage modifier 
	//Should persist the submission of a charge in order to have re-issue functionality.
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
		
		//Initialise any actions relevant to the menu (selecting players, charges, editting selectedfields)
		m_wRoot = GetRootWidget();
		
		if (!m_wRoot)
		{
			Print("Error in Layout Tutorial layout creation", LogLevel.ERROR);
			return;
		}
		
		m_wPlayerList = VerticalLayoutWidget.Cast(m_wRoot.FindAnyWidget(PLAYERS_CONTAINER_NAME));
		m_wChargeList = VerticalLayoutWidget.Cast(m_wRoot.FindAnyWidget(CHARGES_CONTAINER_NAME));
		
		if (!m_wPlayerList)
		{
			Print("Unable to find container for player list", LogLevel.ERROR);
			return;
		}
		
		this.PopulatePlayerListContainer();
		this.PopulateChargeListContainer();
	}
	
	//------------------------------------------------------------------------------------------------
	void PopulatePlayerListContainer(){
		
		array<ref DummyPlayer> players = EL_TestData.GetPlayerList(20);
		
		foreach (DummyPlayer player : players)
		{
			ButtonWidget wTicketingSinglePlayerItem = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets(LIST_ITEM_LAYOUT, m_wPlayerList));
			TextWidget newPlayerEntryText = TextWidget.Cast(wTicketingSinglePlayerItem.FindAnyWidget("Text"));
			
			//Create a button and assign player properties.
			newPlayerEntryText.SetText(player.m_name);
			
			//Add the button as a child to the preview list. 
			m_wPlayerList.AddChild(wTicketingSinglePlayerItem);
			m_wPlayerList.Update();
		}
	
	}
	
	//------------------------------------------------------------------------------------------------
	void PopulateChargeListContainer(){
		
		array<ref DummyCharge> charges = EL_TestData.GetChargeList(30);
		
		foreach (DummyCharge charge : charges)
		{
			ButtonWidget wTicketingSingleChargeItem = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets(LIST_ITEM_LAYOUT, m_wChargeList));
			TextWidget newSingleChargeEntryText = TextWidget.Cast(wTicketingSingleChargeItem.FindAnyWidget("Text"));
			
			//Create a button and assign charge properties.
			newSingleChargeEntryText.SetText(charge.m_name);
			
			//Add the button as a child to the preview list. 
			m_wChargeList.AddChild(wTicketingSingleChargeItem);
			m_wChargeList.Update();
		}
	
	}
}