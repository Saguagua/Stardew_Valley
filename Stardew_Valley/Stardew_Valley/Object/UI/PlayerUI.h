#pragma once
class PlayerUI
{
	PlayerUI();
	~PlayerUI() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new PlayerUI();
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
	
private:
	void Key();
	
	static PlayerUI* _instance;
	shared_ptr<Transform> _transform;
	shared_ptr<class BagUI> _bagUI;
	shared_ptr<class ItemSlot> _itemSlot;
	shared_ptr<class Bar> _hpBar;
	shared_ptr<class Bar> _staminaBar;
	shared_ptr<class TimeUI> _timeUI;

	bool _bagActive;
};

