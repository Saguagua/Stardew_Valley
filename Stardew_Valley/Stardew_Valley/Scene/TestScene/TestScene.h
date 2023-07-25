#pragma once
class TestScene :public Scene
{
public:
	TestScene();
	virtual ~TestScene() {}

	virtual void Update() override;
	virtual void Render() override;

private:
	Vector2 curF = { 0,0 };
	shared_ptr<class TileMap> _homeMap;
	shared_ptr<class TileMap> _farmmingMap;
	shared_ptr<class TileMap> _beachMap;
	shared_ptr<class TileMap> _dungeonMap;

	shared_ptr<class Player> _player;
};