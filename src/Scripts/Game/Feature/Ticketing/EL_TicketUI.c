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
	protected ref array<int> m_aSelectedPlayerIds;
	protected ref array<int> m_aSelectedChargeIds;
	
	protected const string LIST_ITEM_LAYOUT = "{68E6F89F53D27CD3}UI/layouts/Menus/ContentBrowser/Buttons/ContentBrowser_ModularButtonText.layout";
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
		m_aSelectedPlayerIds = {};
		m_aSelectedChargeIds = {};
		
		this.PopulatePlayerListContainer();
		this.PopulateChargeListContainer();
	}
	
	//------------------------------------------------------------------------------------------------
	void UpdatePlayerList(int selectedPlayerId)
	{
		Print("Selected player: " + selectedPlayerId);
	}
	
	//------------------------------------------------------------------------------------------------
	//To change handler to SCR_ButtonTextComponent
	void OnPlayerSelected(SCR_ModularButtonComponent clickedbuttonComponent, bool isToggled)
	{
		//Might give issue since GetData return type is managed.
		DummyPlayer selectedPlayer = DummyPlayer.Cast(clickedbuttonComponent.GetData());
		
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
			
			//Format root button
			LayoutSlot.SetPadding(wSinglePlayerButton, 0, 0, 0, 10);
			
			//Format text
			LayoutSlot.SetHorizontalAlign(wSinglePlayerNameText, LayoutHorizontalAlign.Left);
			LayoutSlot.SetVerticalAlign(wSinglePlayerNameText, LayoutVerticalAlign.Center);
			//LayoutSlot.SetPadding(wSinglePlayerNameText, 10, 0, 0, 0); 
			wSinglePlayerNameText.SetText(player.m_name);
			wSinglePlayerNameText.SetExactFontSize(25);
			
			//Format button size
			wSinglePlayerSize.SetHeightOverride(60);
			
			buttonHandler.SetEffectsEnabled("MISSING TAG??", false);
			
			foreach(SCR_ButtonEffectBase buttonEffect : buttonHandler.GetAllEffects())
			{
				Print("Effect Tag: " + buttonEffect.m_aTags.ToString());
			}
			
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
			VerticalLayoutWidget wTicketingSingleChargeItem = VerticalLayoutWidget.Cast(GetGame().GetWorkspace().CreateWidgets(QUANT_LIST_ITEM_LAYOUT, m_wChargeList));
			TextWidget newSingleChargeEntryText = TextWidget.Cast(wTicketingSingleChargeItem.FindAnyWidget("ButtonText"));
			
			//Find the AddButton and ReduceButton 
			//Add handlers for AddButton and ReduceButton.
			//Can be the same handler and are a ButtonWidget so they behave the same.
			//If the charge quantity is higher than 1 then enable.
			
			
			//Create a button and assign charge properties.
			newSingleChargeEntryText.SetText(charge.m_name);
			
			//Add the button as a child to the preview list. 
			m_wChargeList.AddChild(wTicketingSingleChargeItem);
			m_wChargeList.Update();
		}
	
	}
}