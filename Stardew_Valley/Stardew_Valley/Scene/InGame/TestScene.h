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
	shared_ptr<class TileMap> _tileMap;
	shared_ptr<class Tile> _tile;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
	shared_ptr<class CircleCollider> _circle;
	shared_ptr<class RectCollider> _rect;
};