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
	virtual void WhenCoverDark() override;
private:
	void KeyInput();

	shared_ptr<PlayerImproved> _player;
	shared_ptr<TileMap> _map;
	shared_ptr<TeleportInfo> _teleportInfo;

	CallBack _cb;
};