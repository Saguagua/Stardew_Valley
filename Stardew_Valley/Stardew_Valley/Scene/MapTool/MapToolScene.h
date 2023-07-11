#pragma once
class MapToolScene :public Scene
{
public:
	MapToolScene();
	virtual ~MapToolScene() {}

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:

	shared_ptr<TileMap> _map;
	shared_ptr<Palette> _palette;
	ofstream _fout;
	ofstream _fout2;
	ifstream _fin;
};

