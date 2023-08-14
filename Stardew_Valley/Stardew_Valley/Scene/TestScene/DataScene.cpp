#include "framework.h"
#include "DataScene.h"

DataScene::DataScene()
{
	ObjectSpawner::Create();
	LightManager::Create();
	DATA->Load("Test");
	_map = make_shared<TileMap>();
}

DataScene::~DataScene()
{
	ObjectSpawner::Delete();
	LightManager::Delete();
}

void DataScene::Update()
{
	LightManager::GetInstance()->Update();
	_map->Update();
}

void DataScene::Render()
{
	_map->Render();
}
