#include "framework.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	_palette = make_shared<Palette>(Vector2(300, 400));
}

void MapToolScene::Update()
{
	_palette->Update();
}

void MapToolScene::Render()
{
	
}

void MapToolScene::PostRender()
{
	_palette->PostRender();
}
