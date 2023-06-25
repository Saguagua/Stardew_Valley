#pragma once
class TestScene :public Scene
{
public:
	TestScene();
	virtual ~TestScene() {}

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<class TileMap> _tileMap;
	shared_ptr<class Tile> _tile;
};