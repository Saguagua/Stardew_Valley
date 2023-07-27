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
	void LoadMaps(string playerName);
	void LoadMap(string playerName, string mapName);
	void LoadPlayerInfo(string playerName);

	static DataManager* _instance;
	shared_ptr<PlayerInfo> _playerInfo;
	vector<shared_ptr<MapInfo>> _mapInfos;
	vector<shared_ptr<ObjectInfo>> _objInfos;
	vector<shared_ptr<TileInfo>> _tileInfos;
	unordered_map<string, bool> _mapTable;
	unordered_map<string, bool> _playerTable;

	Vector2 _tileMaxFrame;
	Vector2 _objectMaxFrame;
};