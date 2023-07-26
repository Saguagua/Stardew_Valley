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

	void SaveMaps(vector<shared_ptr<class MapInfo>> infos);
	shared_ptr<MapInfo> LoadMap(string mapName);

	Vector2 GetTileMaxFrame() { return _tileMaxFrame; }
	Vector2 GetObjectMaxFrame() { return _objectMaxFrame; }

	vector<shared_ptr<MapInfo>> GetMapInfos() { return _mapInfos; }
	shared_ptr<class PlayerInfo> GetPlayerInfo() { return _playerInfo; }

	vector<shared_ptr<class TileInfo>>& GetTileInfos() { return _tileInfos; }
	shared_ptr<class TileInfo> GetTileInfo(int tileCode) { return _tileInfos[tileCode]; }
	vector<shared_ptr<class ObjectInfo>> GetObjectInfos() { return _objInfos; }
	shared_ptr<ObjectInfo> GetObjectInfo(int index) { return _objInfos[index]; }

	void ReadMaps();
private:
	void ReadTileTypes();
	void ReadObjectFile();
	void ReadPlayerFile();

	static DataManager* _instance;
	shared_ptr<PlayerInfo> _playerInfo;
	vector<shared_ptr<MapInfo>> _mapInfos;
	unordered_map<string, bool> _mapTable;
	vector<shared_ptr<ObjectInfo>> _objInfos;
	vector<shared_ptr<TileInfo>> _tileInfos;

	Vector2 _tileMaxFrame;
	Vector2 _objectMaxFrame;

	ofstream _fout;
	ifstream _fin;
};