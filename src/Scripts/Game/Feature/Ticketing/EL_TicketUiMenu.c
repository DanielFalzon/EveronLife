//This class will handle any functionalities needed when the player interacts with the menu
//Look at SCR_PlayerListMenu.CreateEntry
//Look at 

class EL_TicketUiMenu : ChimeraMenuBase
{
	protected  Widget m_wRoot;
	protected VerticalLayoutWidget m_wPlayerList;
	protected VerticalLayoutWidget m_wChargeList;
	
	EL_TicketUiManagerComponent m_ticketUiManagerComponent;

	protected ref map<int, ref DummyPlayer> m_playerList;
	protected ref map<int, ref DummyCharge> m_chargeList;
	protected ref array<int> m_aSelectedPlayerIds;
	protected ref map<int, int> m_aSelectedChargeQuantities;
	
	protected const string LIST_ITEM_LAYOUT = "{8052667FD5E6D112}UI/Layouts/WidgetLibrary/Buttons/EL_ItemListButton.layout";
	protected const string QUANT_LIST_ITEM_LAYOUT = "{B85C13E4B2C21DEC}UI/Layouts/WidgetLibrary/Buttons/EL_QuantityItemListButton.layout";
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
		
		
	}
	
	//------------------------------------------------------------------------------------------------
	void SetTicketManager(EL_TicketUiManagerComponent ticketManager)
	{
		m_ticketUiManagerComponent = ticketManager;
	}
	
	//------------------------------------------------------------------------------------------------
	void UpdatePlayerList(int selectedPlayerId)
	{
		Print("Selected player: " + selectedPlayerId);
	}
	
	//------------------------------------------------------------------------------------------------
	void OnPlayerSelected(SCR_ModularButtonComponent clickedPlayerComponent, bool isToggled)
	{
		DummyPlayer selectedPlayer = DummyPlayer.Cast(clickedPlayerComponent.GetData());
		m_ticketUiManagerComponent.TogglePlayer(selectedPlayer, isToggled);
	}
	
	//------------------------------------------------------------------------------------------------
	string FormatChargeText(string chargename, int chargeQuantity)
	{
		if (chargeQuantity > 0)
		{
			return chargename + "(" + chargeQuantity.ToString() + ")";
		} else {
			return chargename;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void OnAddChargeClicked(SCR_ModularButtonComponent removeChargeComponent)
	{
		DummyCharge charge = DummyCharge.Cast(removeChargeComponent.GetData());
		int newQuantity = m_ticketUiManagerComponent.AddCharge(charge);
		
		//Get the charge
		HorizontalLayoutWidget wParent = HorizontalLayoutWidget.Cast(removeChargeComponent.GetRootWidget().GetParent());
		ButtonWidget wRemoveButton = ButtonWidget.Cast(wParent.FindAnyWidget("RemoveButton"));
		TextWidget wButtonText = TextWidget.Cast(wParent.FindAnyWidget("ButtonText"));
		
		if(!wRemoveButton.IsEnabled()) wRemoveButton.SetEnabled(true);
		wButtonText.SetText(FormatChargeText(charge.m_name, newQuantity));

		return;
	}
	
	//------------------------------------------------------------------------------------------------
	void OnRemoveChargeClicked(SCR_ModularButtonComponent removeChargeComponent)
	{	
		DummyCharge charge = DummyCharge.Cast(removeChargeComponent.GetData());
		int newQuantity = m_ticketUiManagerComponent.RemoveCharge(charge);
		
		if (newQuantity == -1) return;
		
		ButtonWidget wRoot = ButtonWidget.Cast(removeChargeComponent.GetRootWidget());
		HorizontalLayoutWidget wParent = HorizontalLayoutWidget.Cast(wRoot.GetParent());
		ButtonWidget wAddButton = ButtonWidget.Cast(wParent.FindAnyWidget("AddButton"));
		TextWidget wButtonText = TextWidget.Cast(wParent.FindAnyWidget("ButtonText"));
		
		wButtonText.SetText(FormatChargeText(charge.m_name, newQuantity));
		
		if (newQuantity == 0) wRoot.SetEnabled(false);
	
		return;
	}
	
	//------------------------------------------------------------------------------------------------
	void PopulatePlayerListContainer()
	{
		foreach (DummyPlayer player : m_ticketUiManagerComponent.GetPlayerList())
		{
			ButtonWidget wSinglePlayerButton = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets(LIST_ITEM_LAYOUT, m_wPlayerList));
			TextWidget wSinglePlayerNameText = TextWidget.Cast(wSinglePlayerButton.FindAnyWidget("Text"));
			SizeLayoutWidget wSinglePlayerSize = SizeLayoutWidget.Cast(wSinglePlayerButton.FindAnyWidget("Size"));
			
			SCR_ModularButtonComponent buttonHandler = SCR_ModularButtonComponent.Cast(wSinglePlayerButton.FindHandler(SCR_ModularButtonComponent));
			//State to be stored in a class inheriting from Managed
			buttonHandler.m_OnToggled.Insert(OnPlayerSelected);
			buttonHandler.SetData(player);
			buttonHandler.SetEffectsEnabled("on-toggle-change-text", false);
			
			//Format root button
			LayoutSlot.SetPadding(wSinglePlayerButton, 0, 0, 10, 10);
			
			//Format text
			LayoutSlot.SetHorizontalAlign(wSinglePlayerNameText, LayoutHorizontalAlign.Left);
			LayoutSlot.SetVerticalAlign(wSinglePlayerNameText, LayoutVerticalAlign.Center);
			//LayoutSlot.SetPadding(wSinglePlayerNameText, 10, 0, 0, 0); 
			wSinglePlayerNameText.SetText(player.m_name);
			wSinglePlayerNameText.SetExactFontSize(25);
			
			//Format button size
			wSinglePlayerSize.SetHeightOverride(60);
			
			//Add the button as a child to the preview list. 
			m_wPlayerList.AddChild(wSinglePlayerButton);
			m_wPlayerList.Update();
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void PopulateChargeListContainer()
	{
		foreach (DummyCharge charge : m_ticketUiManagerComponent.GetChargeList())
		{
			VerticalLayoutWidget wSingleChargeItem = VerticalLayoutWidget.Cast(GetGame().GetWorkspace().CreateWidgets(QUANT_LIST_ITEM_LAYOUT, m_wChargeList));
			TextWidget wSingleChargeText = TextWidget.Cast(wSingleChargeItem.FindAnyWidget("ButtonText"));
			ButtonWidget wAddChargeButton = ButtonWidget.Cast(wSingleChargeItem.FindAnyWidget("AddButton"));
			ButtonWidget wRemoveChargeButton = ButtonWidget.Cast(wSingleChargeItem.FindAnyWidget("RemoveButton"));
			
			//Add handlers & charge ID for AddButton and ReduceButton.
			SCR_ModularButtonComponent addChargeButtonHandler = SCR_ModularButtonComponent.Cast(wAddChargeButton.FindHandler(SCR_ModularButtonComponent));
			SCR_ModularButtonComponent removeChargeButtonHandler = SCR_ModularButtonComponent.Cast(wRemoveChargeButton.FindHandler(SCR_ModularButtonComponent));
			
			addChargeButtonHandler.SetData(charge);
			removeChargeButtonHandler.SetData(charge);
			
			addChargeButtonHandler.m_OnClicked.Insert(OnAddChargeClicked);
			removeChargeButtonHandler.m_OnClicked.Insert(OnRemoveChargeClicked);
									
			wSingleChargeText.SetText(charge.m_name);
			
			m_wChargeList.AddChild(wSingleChargeItem);
			m_wChargeList.Update();
		}
	
	}
}