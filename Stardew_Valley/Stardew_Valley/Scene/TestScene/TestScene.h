#pragma once
class TestScene :public Scene
{
public:
	TestScene();
	~TestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void Initialize() override;
private:
	void KeyInput();


	shared_ptr<PlayerFight> _player;
	shared_ptr<TileMap> _map;
	vector<shared_ptr<Item>> _items;

	shared_ptr<RectCollider> _nextArea;

};