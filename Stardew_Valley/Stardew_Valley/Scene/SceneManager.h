#pragma once
class SceneManager
{
	SceneManager();
	~SceneManager() {}

public:
	enum SceneIndex
	{
		MAPTOOL,
		TEST,
		NORMAL,
		DUNGEON
	};

	static void Create()
	{
		if (_instance == nullptr)
			_instance = new SceneManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static SceneManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void Update();

	void Render();

	void PostRender();

	int _index = 0;
	bool _changeScene;
private:
	static SceneManager* _instance;

	vector<shared_ptr<Scene>> _scenes;
};

