class EL_TestData
{
	static array<ref DummyPlayer> GetPlayerList(int count)
	{
		array<ref DummyPlayer> result = {};
		
		for(int i = 0; i < count; i++)
		{
			result.Insert(new DummyPlayer(count, "Name Test " + i));
		}
		
		return result;
	};
	
	static array<ref DummyCharge> GetChargeList(int count)
	{
		array<ref DummyCharge> result = {};
		
		for(int i = 0; i < count; i++)
		{
			result.Insert(new DummyCharge(i, "Charge Test " + i, i * 10, i * 100));
		}
		
		return result;
	}
}

class DummyPlayer
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