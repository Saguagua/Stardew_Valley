#pragma once
class PlayerUI
{
	PlayerUI(shared_ptr<PlayerImproved> player);
	~PlayerUI() {}

public:
	static void Create(shared_ptr<PlayerImproved> player)
	{
		if (_instance == nullptr)
			_instance = new PlayerUI(player);
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static PlayerUI* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return _instance;
	}

	void PostRender();
	void Update();

	void NextDay();

	void SetHP(float hp);
	void SetStamina(float stamina);
	
	void SetBagMode(bool val);
	bool GetBagActive() { return _bagActive; }
	void SetSaleMode(bool val);
private:
	void Key();
	bool _bagActive;
	
	static PlayerUI* _instance;

	shared_ptr<Transform> _transform;

	shared_ptr<class BagUI> _bagUI;
	shared_ptr<class ItemSlot> _itemSlot;
	shared_ptr<class Bar> _hpBar;
	shared_ptr<class Bar> _staminaBar;
	shared_ptr<class TimeUI> _timeUI;
};

