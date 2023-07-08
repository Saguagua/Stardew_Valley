#include "framework.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	_palette = make_shared<Palette>(Vector2(400, 600));
	_map = make_shared<TileMap>(Vector2(50, 50));
}

void MapToolScene::Update()
{
	_map->Update();
	_palette->Update();
}

void MapToolScene::Render()
{
	_map->Render();
}

void MapToolScene::PostRender()
{
	_palette->PostRender();
}
