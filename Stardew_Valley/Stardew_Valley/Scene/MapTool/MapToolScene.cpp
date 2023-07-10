#include "framework.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	_palette = make_shared<Palette>(Vector2(450, 600));
	_map = make_shared<TileMap>(Vector2(50, 50), _palette);
	_map->SetActive(true);
}

void MapToolScene::Update()
{
	_palette->Update();
	_map->Update();
}

void MapToolScene::Render()
{
	_map->Render();
}

void MapToolScene::PostRender()
{
	_palette->PostRender();
}


void MapToolScene::Save(string filename)
{
	_fin.open(filename);


}

void MapToolScene::Load(string filename)
{
	_fout.open(filename);


}
