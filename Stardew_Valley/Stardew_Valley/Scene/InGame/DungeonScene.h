#pragma once
class DungeonScene :public Scene
{
public:
	DungeonScene(shared_ptr<PlayerFight> p);
	~DungeonScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;


private:
	void KeyInput();

	weak_ptr<PlayerFight> _player;
	shared_ptr<TileMap> _map;
	vector<shared_ptr<Item>> _items;

	shared_ptr<Door> _door;

	int _stair = 1;
	int _mapCount;
};

