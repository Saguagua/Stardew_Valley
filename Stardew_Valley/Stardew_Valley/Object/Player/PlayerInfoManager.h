#pragma once
class PlayerInfoManager
{
private:
	PlayerInfoManager();
	~PlayerInfoManager() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new PlayerInfoManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static PlayerInfoManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	shared_ptr<class PlayerInfo> GetInfo()
	{
		return _info;
	}

	void AddHP(short amount);
	void AddMaxHP(short amount);
	void AddStamina(short amount);
	void AddMaxStamina(short amount);
private:
	void SetPlayerInfo();

	static PlayerInfoManager* _instance;

	shared_ptr<PlayerInfo> _info;
	string _name;
};

