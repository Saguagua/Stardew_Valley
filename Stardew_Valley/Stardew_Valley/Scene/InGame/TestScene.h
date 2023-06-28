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
	shared_ptr<class Character> _character;

};