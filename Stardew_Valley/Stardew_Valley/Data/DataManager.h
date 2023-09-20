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

	vector<shared_ptr<MapInfo>>& GetPlayerMapInfos() { return _playerMapInfos; }
	vector<shared_ptr<MapInfo>>& GetInitialMapInfos() { return _initialMapInfos; }
	vector<shared_ptr<MapInfo>>& GetDungeonMapInfos() { return _dungeonMapInfos; }

	shared_ptr<class PlayerInfo> GetPlayerInfo() { return _playerInfo; }

	unordered_map<string, shared_ptr<class XMLInfo>>& GetXMLInfos() { return _xmlTable; }
	shared_ptr<XMLInfo> GetXMLInfo(string key) { return _xmlTable[key]; }

	unordered_map<string, int>& GetTileInfos() { return _tileTable; }
	int GetTileInfo(string tileName) { return _tileTable[tileName]; }

	unordered_map<string, shared_ptr<DropInfo>>&	GetDropInfos()	{ return _dropTable; }
	unordered_map<string, shared_ptr<DeployInfo>>&	GetDeployInfos(){ return _deployTable; }
	unordered_map<string, shared_ptr<ItemInfo>>&	GetItemInfos()	{ return _itemTable; }
	unordered_map<string, shared_ptr<CropInfo>>&	GetCropInfos()	{ return _cropTable; }
	vector<shared_ptr<FishInfo>>& GetFishInfos() { return _fishTable; }
	unordered_map<string, shared_ptr<SaleInfo>>& GetSaleInfos() { return _saleTable; }

	shared_ptr<DropInfo>	GetDropInfo(string key)		{ return _dropTable[key]; }
	shared_ptr<DeployInfo>	GetDeployInfo(string key)	{ return _deployTable[key]; }
	shared_ptr<ItemInfo>	GetItemInfo(string key)		{ return _itemTable[key]; }
	shared_ptr<CropInfo>	GetCropInfo(string key)		{ return _cropTable[key]; }
	shared_ptr<SaleInfo>    GetSaleInfo(string key)		{ return _saleTable[key]; }
	vector<pair<string, int>> GetSpawnInfo(int mapIndex)  { return _spawnTable[mapIndex]; }

	void MapToolSave();
	void PlaySave();

	void LoadInitialMaps();
	void LoadMaps(string name);
	void LoadPlayerInfo(string playerName);

	int _month;
	int _day;
private:
	void ReadXML();
	void ReadTypes();
	void ReadPlayers();
	void ReadMaps();

	void SaveMaps();
	void SavePlayerInfo();

	shared_ptr<MapInfo> LoadMap(string path, string mapName);

	static DataManager* _instance;

	shared_ptr<PlayerInfo> _playerInfo;
	
	unordered_map<string, bool> _playerTable;
	
	vector<shared_ptr<MapInfo>> _playerMapInfos;
	vector<shared_ptr<MapInfo>> _initialMapInfos;
	vector<shared_ptr<MapInfo>> _dungeonMapInfos;
	
	vector<shared_ptr<FishInfo>> _fishTable;

	unordered_map<string, bool> _mapTable;

	unordered_map<string, int> _tileTable;

	unordered_map<string, shared_ptr<XMLInfo>> _xmlTable;
	unordered_map<string, shared_ptr<DropInfo>> _dropTable;
	unordered_map<string, shared_ptr<ItemInfo>> _itemTable;
	unordered_map<string, shared_ptr<CropInfo>> _cropTable;
	unordered_map<string, shared_ptr<SaleInfo>> _saleTable;
	unordered_map<string, shared_ptr<DeployInfo>> _deployTable;
	vector<vector<pair<string, int>>> _spawnTable;
};