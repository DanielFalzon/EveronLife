//This class will handle any functionalities needed when the player interacts with the menu
//Look at SCR_PlayerListMenu.CreateEntry
//Look at 

class EL_TicketUI : ChimeraMenuBase
{
	protected  Widget m_wRoot;
	protected VerticalLayoutWidget m_wPlayerList;
	protected VerticalLayoutWidget m_wChargeList;
	//TAG_EventHolder <- Invoker of event
	protected EL_SelectableListItemButton m_wSelectableItemButton;
	
	protected ref map<int, ref DummyPlayer> m_playerList;
	protected ref map<int, ref DummyCharge> m_chargeList;
	protected ref array<int> m_selectedPlayerIdList;
	protected ref array<int> m_selectedChargeIdList;
	
	protected const string LIST_ITEM_LAYOUT = "{482EDF389BB71398}UI/Layouts/WidgetLibrary/EL_SelectableListItem.layout";
	protected const string QUANT_LIST_ITEM_LAYOUT = "{1350A93B50CCAB79}UI/Layouts/WidgetLibrary/EL_QuantityListItem.layout";
	protected const string PLAYERS_CONTAINER_NAME = "PlayerListButtonContainer";
	protected const string CHARGES_CONTAINER_NAME = "ChargeListContainer";
	
	//Variables should hold array of players, charges, percentage modifier 
	//Should persist the submission of a charge in order to have re-issue functionality.
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
		
		//Initialise any actions relevant to the menu (selecting players, charges, editting selectedfields)
		m_wRoot = GetRootWidget();
		
		if (!m_wRoot)
		{
			Print("Error in Layout layout creation", LogLevel.ERROR);
			return;
		}
		
		m_wPlayerList = VerticalLayoutWidget.Cast(m_wRoot.FindAnyWidget(PLAYERS_CONTAINER_NAME));
		m_wChargeList = VerticalLayoutWidget.Cast(m_wRoot.FindAnyWidget(CHARGES_CONTAINER_NAME));
		
		if (!m_wPlayerList || !m_wChargeList)
		{
			Print("Unable to find container for player or charge list", LogLevel.ERROR);
			return;
		}
		
		m_playerList = EL_TestData.GetPlayerList(15);
		m_chargeList = EL_TestData.GetChargeList(30);
		m_selectedPlayerIdList = {};
		m_selectedChargeIdList = {};
		
		this.PopulatePlayerListContainer();
		this.PopulateChargeListContainer();
	}
	
	//------------------------------------------------------------------------------------------------
	void UpdatePlayerList(int selectedPlayerId)
	{
		Print("Selected player: " + selectedPlayerId);
	}
	
	//------------------------------------------------------------------------------------------------
	void OnPlayerSelected(EL_SelectableListItemButton wSelectableListItemButton, bool isToggled)
	{
		//THEBONBON: Handler subscribing to the event
		TextWidget wSelectedEntityId = TextWidget.Cast(wSelectableListItemButton.GetRootWidget().FindAnyWidget("EntityId"));
		int selectedEntityId = wSelectedEntityId.GetText().ToInt();
		
		bool addCondition = isToggled && !m_selectedPlayerIdList.Contains(selectedEntityId);
		
		//TODODF: Order alphabetically when inserting / removing;
		if(addCondition){
			m_selectedPlayerIdList.Insert(selectedEntityId);
		}else{
			m_selectedPlayerIdList.RemoveItem(selectedEntityId);
		}
		
		Print("Selected Players: " + m_selectedPlayerIdList.ToString());
	}
	
	//------------------------------------------------------------------------------------------------
	void PopulatePlayerListContainer()
	{
		foreach (DummyPlayer player : m_playerList)
		{
			ButtonWidget wTicketingSinglePlayerItem = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets(LIST_ITEM_LAYOUT, m_wPlayerList));
			TextWidget newPlayerEntryText = TextWidget.Cast(wTicketingSinglePlayerItem.FindAnyWidget("Text"));
			TextWidget newPlayerEntryId = TextWidget.Cast(wTicketingSinglePlayerItem.FindAnyWidget("EntityId")); 
			
			//THEBONBON: Parent UI subscribing to the button's OnToggled event.
			EL_SelectableListItemButton buttonHandler = EL_SelectableListItemButton.Cast(wTicketingSinglePlayerItem.FindHandler(EL_SelectableListItemButton));
			buttonHandler.m_OnToggled.Insert(OnPlayerSelected);
			
			//Create a button and assign player properties.
			newPlayerEntryText.SetText(player.m_name);
			newPlayerEntryId.SetText(player.m_id.ToString());
			
			//Add the button as a child to the preview list. 
			m_wPlayerList.AddChild(wTicketingSinglePlayerItem);
			m_wPlayerList.Update();
		}
	
	}
	
	//------------------------------------------------------------------------------------------------
	void PopulateChargeListContainer()
	{
		foreach (DummyCharge charge : m_chargeList)
		{
			VerticalLayoutWidget wTicketingSingleChargeItem = VerticalLayoutWidget.Cast(GetGame().GetWorkspace().CreateWidgets(QUANT_LIST_ITEM_LAYOUT, m_wChargeList));
			TextWidget newSingleChargeEntryText = TextWidget.Cast(wTicketingSingleChargeItem.FindAnyWidget("ButtonText"));
			
			//Create a button and assign charge properties.
			newSingleChargeEntryText.SetText(charge.m_name);
			
			//Add the button as a child to the preview list. 
			m_wChargeList.AddChild(wTicketingSingleChargeItem);
			m_wChargeList.Update();
		}
	
	}
	
	//------------------------------------------------------------------------------------------------
	void UnSubscribe()
	{
		if (!m_wSelectableItemButton)
			return;

		m_wSelectableItemButton.m_OnButtonSelected.Remove(UpdatePlayerList);
		m_wSelectableItemButton = null;
	}
	
	//------------------------------------------------------------------------------------------------
	void ~EL_TicketUI()
	{
		UnSubscribe();
	}
}