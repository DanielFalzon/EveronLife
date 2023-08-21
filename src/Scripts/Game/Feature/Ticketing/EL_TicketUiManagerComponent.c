//This class will handle providing any data required to the m_TicketUI layout
[EntityEditorProps(category: "EL/Ticket")]
class EL_TicketUiManagerComponentClass : ScriptComponentClass
{
}

class EL_TicketUiManagerComponent: ScriptComponent
{
	EL_TicketUiMenu m_TicketUiMenu;
	
	protected ref map<int, ref DummyPlayer> m_playerList;
	protected ref map<int, ref DummyCharge> m_chargeList;
	protected ref array<int> m_aSelectedPlayerIds;
	protected ref map<int, int> m_aSelectedChargeQuantities;
	
	//------------------------------------------------------------------------------------------------
	//! Public API
	
	//------------------------------------------------------------------------------------------------
	void OpenTicketUI(float value = 0.0, EActionTrigger trigger = 0)
	{
		SetPlayerList();
		SetChargeList();
		
		m_TicketUiMenu = EL_TicketUiMenu.Cast(GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.EL_TicketUiMenu));
		m_TicketUiMenu.SetTicketManager(this);
		
		m_TicketUiMenu.PopulatePlayerListContainer();
		m_TicketUiMenu.PopulateChargeListContainer();
	}
	
	//------------------------------------------------------------------------------------------------
	map<int, ref DummyPlayer> GetPlayerList()
	{
		return m_playerList;
	}
	
	//------------------------------------------------------------------------------------------------
	map<int, ref DummyCharge> GetChargeList()
	{
		return m_chargeList;
	}
	
	
	//------------------------------------------------------------------------------------------------
	void TogglePlayer(DummyPlayer player, bool isToggled)
	{	
		//TODODF: Order alphabetically when inserting / removing;
		if(isToggled){
			m_aSelectedPlayerIds.Insert(player.m_id);
		}else{
			m_aSelectedPlayerIds.RemoveItem(player.m_id);
		}
		
		Print("Selected Players: " + m_aSelectedPlayerIds.ToString());
	}
	
	//------------------------------------------------------------------------------------------------
	int AddCharge(DummyCharge charge)
	{
		int quantity = 1;
		
		if (m_aSelectedChargeQuantities.Contains(charge.m_id))
		{
			quantity += m_aSelectedChargeQuantities.Get(charge.m_id);
		}
		
		m_aSelectedChargeQuantities.Set(charge.m_id, quantity);
		
		return quantity;
	}
	
	//------------------------------------------------------------------------------------------------
	int RemoveCharge(DummyCharge charge)
	{
		if(!m_aSelectedChargeQuantities.Contains(charge.m_id)) return -1;
		
		int quantity = m_aSelectedChargeQuantities.Get(charge.m_id);
		
		if(quantity == 1){
			m_aSelectedChargeQuantities.Remove(charge.m_id);
			return 0;
		}
		
		quantity -= 1;
		
		m_aSelectedChargeQuantities.Set(charge.m_id, quantity);
		
		return quantity;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Protected API
	
	//------------------------------------------------------------------------------------------------
	protected void SetPlayerList()
	{
		m_playerList = EL_TestData.GetPlayerList(35);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void SetChargeList()
	{
		m_chargeList = EL_TestData.GetChargeList(30);
	}
}