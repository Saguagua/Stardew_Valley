#pragma once
class MoneyManager
{
	MoneyManager();
	~MoneyManager() {}
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new MoneyManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}


	static MoneyManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();

	shared_ptr<Item> GetTopItem();

	shared_ptr<Item> Undo();

	void SaleItem(shared_ptr<Item> item);

	short _farmmingPrice;
	short _fishingPrice;
	short _miningPrice;
	short _extraPrice;
	short _priceSum;

	int& _playerMoney = DATA->GetPlayerInfo()->GetMoney();
private:
	static MoneyManager* _instance;

	enum Type
	{
		FARM,
		FISH,
		MINE,
		EXTRA
	};

	stack<shared_ptr<Item>> _saleItems;


};

