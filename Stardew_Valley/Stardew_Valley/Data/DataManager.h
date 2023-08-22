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

	vector<shared_ptr<class MapInfo>>& GetMapInfos() { return _mapInfos; }

	shared_ptr<class PlayerInfo> GetPlayerInfo() { return _playerInfo; }

	unordered_map<string, shared_ptr<class XMLInfo>>& GetXMLInfos() { return _xmlTable; }
	shared_ptr<XMLInfo> GetXMLInfo(string key) { return _xmlTable[key]; }

	unordered_map<string, int>& GetTileInfos() { return _tileTable; }
	int GetTileInfo(string tileName) { return _tileTable[tileName]; }

	unordered_map<string, shared_ptr<DropInfo>>&	GetDropInfos()	{ return _dropTable; }
	unordered_map<string, shared_ptr<DeployInfo>>&	GetDeployInfos(){ return _deployTable; }
	unordered_map<string, shared_ptr<ItemInfo>>&	GetItemInfos()	{ return _itemTable; }
	unordered_map<string, shared_ptr<CropInfo>>&	GetCropInfos()	{ return _cropTable; }

	shared_ptr<DropInfo>	GetDropInfo(string key)		{ return _dropTable[key]; }
	shared_ptr<DeployInfo>	GetDeployInfo(string key)	{ return _deployTable[key]; }
	shared_ptr<ItemInfo>	GetItemInfo(string key)		{ return _itemTable[key]; }
	shared_ptr<CropInfo>	GetCropInfo(string key)		{ return _cropTable[key]; }

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
	
	unordered_map<string, bool> _playerTable;
	
	vector<shared_ptr<MapInfo>> _mapInfos;
	unordered_map<string, bool> _mapTable;
	
	unordered_map<string, shared_ptr<XMLInfo>> _xmlTable;
					unordered_map<string, int> _tileTable;
	unordered_map<string, shared_ptr<DropInfo>> _dropTable;
	unordered_map<string, shared_ptr<DeployInfo>> _deployTable;
		unordered_map<string, shared_ptr<ItemInfo>> _itemTable;
		unordered_map<string, shared_ptr<CropInfo>> _cropTable;
};