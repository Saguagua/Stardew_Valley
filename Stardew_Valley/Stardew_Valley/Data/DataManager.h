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

	vector<shared_ptr<class MapInfo>>& GetMapInfos() { return _mapInfos; }

	shared_ptr<class PlayerInfo> GetPlayerInfo() { return _playerInfo; }
	shared_ptr<PlayerInfo> RequestPlayerSubScribe(class PlayerSubscribe* subscriber);
	void PlayerNotification(int type);
	void PlayerDeadNotification();
	void AddMaxHP(short amount);
	bool AddHP(short amount);
	void AddMaxStamina(short amount);
	bool AddStamina(short amount);
	void SetState(int state);

	shared_ptr<class Item> GetSelectedItem();
	bool AddItem(int type, string name);
	void SwapItems(int index1, int index2);

	unordered_map<string, shared_ptr<class XMLInfo>>& GetXMLInfos() { return _xmlTable; }

	unordered_map<string, shared_ptr<class TileInfo>>& GetTileInfos() { return _tileTable; }
	shared_ptr<class TileInfo> GetTileInfo(string tileName) { return _tileTable[tileName]; }

	unordered_map<string, shared_ptr<class DropInfo>>& GetDropInfos() { return _dropTable; }
	unordered_map<string, shared_ptr<class DeployInfo>>& GetDeployInfos() { return _deployTable; }
	unordered_map<string, shared_ptr<class ItemInfo>>& GetItemInfos() { return _itemTable; }

	void Save();
	void Load(string name);
private:
	void ReadXML();
	void ReadTypes();
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
	
	unordered_map<string, shared_ptr<class XMLInfo>> _xmlTable;
	unordered_map<string, shared_ptr<class TileInfo>> _tileTable;
	unordered_map<string, shared_ptr<class DropInfo>> _dropTable;
	unordered_map<string, shared_ptr<class DeployInfo>> _deployTable;
	unordered_map<string, shared_ptr<class ItemInfo>> _itemTable;

	Vector2 _tileMaxFrame;
	Vector2 _objectMaxFrame;
};