#include "framework.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	TileMap::Create();
	Palette::Create();
	TILEMAP->SetDebug(true);
	PALETTE->SetPos(CENTER - PALETTE->GetSize());
}

MapToolScene::~MapToolScene()
{
	Palette::Delete();
	TileMap::Delete();
}

void MapToolScene::Update()
{
	PALETTE->Update();
	TILEMAP->Update();
}

void MapToolScene::Render()
{
	TILEMAP->Render();
}

void MapToolScene::PostRender()
{
	PALETTE->PostRender();
}