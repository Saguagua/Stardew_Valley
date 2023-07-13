#pragma once
class SaveManager
{
private:
	SaveManager();
	~SaveManager() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new SaveManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static SaveManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void SaveMap(shared_ptr<MapInfo> info);
	shared_ptr<MapInfo> LoadMap(string mapName);

	Vector2 GetMaxFrame() { return _maxFrame; }
	vector<shared_ptr<MapInfo>> GetMapInfos() { return _mapInfos; }
	vector<int>& GetTypes() { return _frameTypes; }
	
private:
	void ReadMaps();
	void ReadTypes();

	static SaveManager* _instance;

	vector<shared_ptr<MapInfo>> _mapInfos;

	unordered_map<string, bool> _mapTable;
	vector<int> _frameTypes;
	Vector2 _maxFrame;

	ofstream _fout;
	ifstream _fin;
};

