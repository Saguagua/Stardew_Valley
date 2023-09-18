#pragma once
class SceneManager
{
	SceneManager();
	~SceneManager() {}

public:
	enum SceneIndex
	{
		LOGO,
		MAPTOOL,
		TEST,
		DAYEND
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

	void ChangeScene(int index);


	shared_ptr<FrontCover> _cover;
private:
	static SceneManager* _instance;
	int _index = 0;


	vector<shared_ptr<Scene>> _scenes;
};

