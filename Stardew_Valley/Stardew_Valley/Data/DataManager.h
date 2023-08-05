#pragma once
class DataManager
{
private:
	DataManager();
	~DataManager() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new DataManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static DataManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}


	Vector2 GetTileMaxFrame() { return _tileMaxFrame; }
	Vector2 GetObjectMaxFrame() { return _objectMaxFrame; }

	vector<shared_ptr<class MapInfo>> GetMapInfos() { return _mapInfos; }

	shared_ptr<class PlayerInfo> GetPlayerInfo() { return _playerInfo; }
	shared_ptr<PlayerInfo> RequestPlayerSubScribe(class PlayerSubscribe* subscriber);
	void PlayerNotification(int type);
	void PlayerDeadNotification();
	void AddMaxHP(short amount);
	bool AddHP(short amount);
	void AddMaxStamina(short amount);
	bool AddStamina(short amount);
	void SetState(int state);

	shared_ptr<class GameObject> GetSelectedItem();
	bool AddItem(int objCode);
	void SwapItems(int index1, int index2);

	vector<shared_ptr<class TileInfo>>& GetTileInfos() { return _tileInfos; }
	shared_ptr<class TileInfo> GetTileInfo(int tileCode) { return _tileInfos[tileCode]; }
	vector<shared_ptr<class ObjectInfo>> GetObjectInfos() { return _objInfos; }
	shared_ptr<ObjectInfo> GetObjectInfo(int index) { return _objInfos[index]; }

	void Save();
	void Load(string name);
private:
	void ReadTileTypes();
	void ReadObjectFile();
	void ReadPlayers();
	void ReadMaps();

	void SaveMaps();
	void SavePlayerInfo();
	void LoadMap(string playerName, string mapName);
	void LoadPlayerInfo(string playerName);

	static DataManager* _instance;

	shared_ptr<PlayerInfo> _playerInfo;
	vector<PlayerSubscribe*> _playerSubscribers;
	unordered_map<string, bool> _playerTable;
	
	vector<shared_ptr<MapInfo>> _mapInfos;
	unordered_map<string, bool> _mapTable;
	
	vector<shared_ptr<ObjectInfo>> _objInfos;
	
	vector<shared_ptr<TileInfo>> _tileInfos;

	Vector2 _tileMaxFrame;
	Vector2 _objectMaxFrame;
};