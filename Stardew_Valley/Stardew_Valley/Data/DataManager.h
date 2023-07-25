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
	vector<int>& GetTypes() { return _frameTypes; }
	shared_ptr<class PlayerInfo> GetPlayerInfo() { return _playerInfo; }


private:
	void ReadMaps();
	void ReadTileTypes();
	void ReadObjectFile();
	void ReadPlayerFile();

	static DataManager* _instance;
	shared_ptr<PlayerInfo> _playerInfo;
	vector<shared_ptr<MapInfo>> _mapInfos;
	unordered_map<string, bool> _mapTable;
	vector<int> _frameTypes;
	Vector2 _tileMaxFrame;
	Vector2 _objectMaxFrame;

	ofstream _fout;
	ifstream _fin;
};