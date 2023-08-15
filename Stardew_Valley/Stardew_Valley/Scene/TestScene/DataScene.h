#pragma once
class DataScene:public Scene
{
public:
	DataScene();
	virtual ~DataScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:

	shared_ptr<TileMap> _map;
	shared_ptr<Player> _player;
};

