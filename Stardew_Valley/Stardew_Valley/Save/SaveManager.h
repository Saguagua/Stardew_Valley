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
	vector<int>& GetTypes() { return _frameTypes; }

private:
	void ReadMaps();
	void ReadTypes();

	static SaveManager* _instance;

	unordered_map<string, bool> _mapTable;
	vector<int> _frameTypes;

	ofstream _fout;
	ifstream _fin;
};

