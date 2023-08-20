class EL_TestData
{
	static map<int, ref DummyPlayer> GetPlayerList(int count)
	{
		map<int, ref DummyPlayer> result = new map<int, ref DummyPlayer>();
		
		for(int i = 0; i < count; i++)
		{
			result.Set(i, new DummyPlayer(i, "Name Test " + i));
		}
		
		return result;
	};
	
	static map<int, ref DummyCharge> GetChargeList(int count)
	{
		map<int, ref DummyCharge> result = new map<int, ref DummyCharge>();
		
		for(int i = 0; i < count; i++)
		{
			result.Set(i, new DummyCharge(i, "Charge Test " + i, i * 10, i * 100));
		}
		
		return result;
	}
}

class DummyPlayer : Managed
{
	int m_id = -1;
	string m_name = "";
	
	void DummyPlayer(int id, string name)
	{
		m_id = id;
		m_name = name;
	}
}

class DummyCharge
{
	int m_id = -1;
	string m_name = "";
	int m_jailTime = -1;
	int m_ticketPrice = -1;
	
	void DummyCharge(int id, string name, int jailTime, int ticketPrice)
	{
		m_id = id;
		m_name = name;
		m_jailTime = jailTime;
		m_ticketPrice = ticketPrice;
	}

}