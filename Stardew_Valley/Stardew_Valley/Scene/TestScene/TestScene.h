#pragma once
class TestScene :public Scene
{
public:
	TestScene();
	~TestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	static bool _bagMode;
private:
	shared_ptr<Player> _player;
	shared_ptr<TileMap> _map;
};