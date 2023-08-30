#include "framework.h"
#include "../../Object/UI/Palette.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	ObjectSpawner::Create();
	LightManager::Create();
	DATA->LoadPlayerInfo("Test");
	DATA->LoadInitialMaps();
	Palette::Create();

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
}

void MapToolScene::Render()
{
	PALETTE->Render();
}

void MapToolScene::PostRender()
{
	PALETTE->PostRender();
}