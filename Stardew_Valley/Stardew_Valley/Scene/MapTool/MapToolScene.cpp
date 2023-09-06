#include "framework.h"
#include "../../Object/UI/Palette.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	DATA->LoadInitialMaps();
	Palette::Create();

	PALETTE->SetPos(CENTER - PALETTE->GetSize());
}

MapToolScene::~MapToolScene()
{
	Palette::Delete();
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