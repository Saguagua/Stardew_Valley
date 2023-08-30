#include "framework.h"
#include "../../Object/UI/Palette.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	ObjectSpawner::Create();
	LightManager::Create();
	DATA->LoadPlayerInfo("Test");
	DATA->LoadMaps("Test");
	Palette::Create();

	_map = make_shared<TileMap>();
	_map->SetDebug(true);

	PALETTE->SetPos(CENTER - PALETTE->GetSize());
}

MapToolScene::~MapToolScene()
{
	Palette::Delete();
	LightManager::Delete();
	ObjectSpawner::Delete();
}

void MapToolScene::Update()
{
	PALETTE->Update();
	//_map->Update();
}

void MapToolScene::Render()
{
	_map->Render();
}

void MapToolScene::PostRender()
{
	PALETTE->PostRender();
}