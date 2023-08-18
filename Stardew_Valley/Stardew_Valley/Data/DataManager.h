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

	unordered_map<string, int>& GetTileInfos() { return _tileTable; }
	int GetTileInfo(string tileName) { return _tileTable[tileName]; }

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
	
	unordered_map<string, bool> _playerTable;
	
	vector<shared_ptr<MapInfo>> _mapInfos;
	unordered_map<string, bool> _mapTable;
	
	unordered_map<string, shared_ptr<class XMLInfo>> _xmlTable;
					unordered_map<string, int> _tileTable;
	unordered_map<string, shared_ptr<class DropInfo>> _dropTable;
	unordered_map<string, shared_ptr<class DeployInfo>> _deployTable;
		unordered_map<string, shared_ptr<class ItemInfo>> _itemTable;
};