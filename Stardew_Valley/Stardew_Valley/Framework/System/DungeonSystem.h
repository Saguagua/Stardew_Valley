#pragma once
class DungeonSystem
{
	DungeonSystem();
	~DungeonSystem() {}
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new DungeonSystem();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}


	static DungeonSystem* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Render();
	void Update();

	void SetMap(shared_ptr<TileMap> map) { _map = map; }
	void SetPlayer(shared_ptr<PlayerImproved> player) { _player = player; }

	void NextStage();

	void SpawnDoor(Vector2 pos);

	int _breakCount = 0;
	bool _active = false;
private:
	static DungeonSystem* _instance;

	weak_ptr<TileMap> _map;
	weak_ptr<PlayerImproved> _player;

	shared_ptr<Sprite> _renderer;
	shared_ptr<RectCollider> _doorCollider;
	bool _doorSpawned = false;

	int _defaultPercent = 10;
};

