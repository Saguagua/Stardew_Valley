#include "framework.h"
#include "../../Object/UI/Palette.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	ObjectSpawner::Create();
	DATA->Load("Admin");
	TileMap::Create();
	Palette::Create();
	TILEMAP->SetDebug(true);
	PALETTE->SetPos(CENTER - PALETTE->GetSize());
}

MapToolScene::~MapToolScene()
{
	Palette::Delete();
	TileMap::Delete();
	ObjectSpawner::Delete();
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