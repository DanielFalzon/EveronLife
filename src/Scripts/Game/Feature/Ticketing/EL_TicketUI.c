//This class will handle any functionalities needed when the player interacts with the menu
//Look at SCR_PlayerListMenu.CreateEntry
//Look at 

class EL_TicketUI : ChimeraMenuBase
{
	protected  Widget m_wRoot;
	protected VerticalLayoutWidget m_wPlayerList;
	protected VerticalLayoutWidget m_wChargeList;

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
		
		m_playerList = EL_TestData.GetPlayerList(15);
		m_chargeList = EL_TestData.GetChargeList(30);
		m_aSelectedPlayerIds = {};
		m_aSelectedChargeQuantities = new map<int, int>();
		
		this.PopulatePlayerListContainer();
		this.PopulateChargeListContainer();
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
		
		bool addCondition = isToggled && !m_aSelectedPlayerIds.Contains(selectedPlayer.m_id);
		
		//TODODF: Order alphabetically when inserting / removing;
		if(addCondition){
			m_aSelectedPlayerIds.Insert(selectedPlayer.m_id);
		}else{
			m_aSelectedPlayerIds.RemoveItem(selectedPlayer.m_id);
		}
		
		Print("Selected Players: " + m_aSelectedPlayerIds.ToString());
	}
	
	//------------------------------------------------------------------------------------------------
	void OnAddChargeClicked(SCR_ModularButtonComponent removeChargeComponent)
	{
		//Get the charge
		HorizontalLayoutWidget wParent = HorizontalLayoutWidget.Cast(removeChargeComponent.GetRootWidget().GetParent());
		ButtonWidget wRemoveButton = ButtonWidget.Cast(wParent.FindAnyWidget("RemoveButton"));
		TextWidget wButtonText = TextWidget.Cast(wParent.FindAnyWidget("ButtonText"));
		DummyCharge charge = DummyCharge.Cast(removeChargeComponent.GetData());
		
		int quantity = 1;
		
		if (!charge) return;
		
		//Check if charge is already added
		if (m_aSelectedChargeQuantities.Contains(charge.m_id))
		{
			quantity += m_aSelectedChargeQuantities.Get(charge.m_id);
		}
		
		m_aSelectedChargeQuantities.Set(charge.m_id, quantity);
		
		if(!wRemoveButton.IsEnabled()) wRemoveButton.SetEnabled(true);
		wButtonText.SetText(charge.m_name + " (" + quantity + ")");
		
		return;
	}
	
	//------------------------------------------------------------------------------------------------
	void OnRemoveChargeClicked(SCR_ModularButtonComponent removeChargeComponent)
	{	
		//The remove button
		ButtonWidget wRoot = ButtonWidget.Cast(removeChargeComponent.GetRootWidget());
		HorizontalLayoutWidget wParent = HorizontalLayoutWidget.Cast(wRoot.GetParent());
		ButtonWidget wAddButton = ButtonWidget.Cast(wParent.FindAnyWidget("AddButton"));
		TextWidget wButtonText = TextWidget.Cast(wParent.FindAnyWidget("ButtonText"));
		DummyCharge charge = DummyCharge.Cast(removeChargeCompwonent.GetData());
		
		//Check if charge is already added
		if(!m_aSelectedChargeQuantities.Contains(charge.m_id)) return;
		
		int quantity = m_aSelectedChargeQuantities.Get(charge.m_id);
		
		if(quantity == 1){
			m_aSelectedChargeQuantities.Remove(charge.m_id);
			wRoot.SetEnabled(false);
			wButtonText.SetText(charge.m_name);
			Print("OnRemoveChargeClicked to Disable: " + quantity);
			return;
		}
		
		quantity -= 1;
		
		m_aSelectedChargeQuantities.Set(charge.m_id, quantity);
		wButtonText.SetText(charge.m_name + " (" + quantity + ")");
		
		return;
	}
	
	//------------------------------------------------------------------------------------------------
	void PopulatePlayerListContainer()
	{
		foreach (DummyPlayer player : m_playerList)
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
		foreach (DummyCharge charge : m_chargeList)
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