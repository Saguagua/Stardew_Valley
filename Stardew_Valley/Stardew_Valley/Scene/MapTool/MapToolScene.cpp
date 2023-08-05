#include "framework.h"
#include "../../Object/UI/Palette.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	ObjectSpawner::Create();
	DATA->Load("Test");
	Palette::Create();
	_map->SetDebug(true);
	PALETTE->SetPos(CENTER - PALETTE->GetSize());
}

MapToolScene::~MapToolScene()
{
	Palette::Delete();
	ObjectSpawner::Delete();
}

void MapToolScene::Update()
{
	PALETTE->Update();
	_map->Update();
}

void MapToolScene::Render()
{
	_map->Render();
}

void MapToolScene::PostRender()
{
	PALETTE->PostRender();
}