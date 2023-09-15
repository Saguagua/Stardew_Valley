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
	void ChangeMap();

	shared_ptr<PlayerImproved> _player;
	shared_ptr<TileMap> _map;
	shared_ptr<FrontCover> _cover;
	shared_ptr<TeleportInfo> _teleportInfo;
};