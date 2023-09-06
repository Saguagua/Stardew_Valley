#pragma once
class MonsterSpawner
{
	MonsterSpawner();
	~MonsterSpawner() {}
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new MonsterSpawner();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static MonsterSpawner* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
	}

	void SetPlayer(shared_ptr<PlayerFight> player) { _player = player; }
	void SetTileMap(shared_ptr<TileMap> map) { _map = map; }
	void Update();
	void Render();

	void PostRender();

	void Spawn(int count);

private:
	static MonsterSpawner* _instance;

	vector<shared_ptr<Monster>> _monsters;
	weak_ptr<PlayerFight> _player;
	weak_ptr<TileMap> _map;


	std::random_device rd;
};

