#pragma once
class TestScene :public Scene
{
public:
	TestScene();
	~TestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	void KeyInput();
	void MonsterAct();
	shared_ptr<Slime> _slime;
	shared_ptr<PlayerImproved> _player;
	shared_ptr<TileMap> _map;
	vector<shared_ptr<Item>> _items;

	float _moveTimer = 1.0f;
	float _stopTimer = 1.0f;
	Vector2 _dir;
};