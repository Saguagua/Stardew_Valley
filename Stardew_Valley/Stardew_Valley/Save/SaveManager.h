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

	void SaveMap(string mapName, Vector2 size, vector<int> clips);
	void LoadMap(string mapName);

private:
	void ReadMaps();
	void ReadTypes();

	static SaveManager* _instance;

	unordered_map<string, bool> _mapTable;
	vector<int> _clipTypes;

	ofstream _fout;
	ifstream _fin;
};

