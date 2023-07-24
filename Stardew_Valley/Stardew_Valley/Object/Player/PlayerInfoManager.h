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

	shared_ptr<PlayerInfo> GetInfo()
	{
		return _info;
	}

private:
	void GetPlayerInfo();

	static PlayerInfoManager* _instance;

	shared_ptr<PlayerInfo> _info;
	string _name;
	vector<shared_ptr<GameObject>> _items;
	short _hp;
	short _stamina;
};

