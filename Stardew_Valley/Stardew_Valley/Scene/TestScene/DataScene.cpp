#include "framework.h"
#include "DataScene.h"

DataScene::DataScene()
{
	ObjectSpawner::Create();
	DATA->Load("Test");
}

DataScene::~DataScene()
{
	ObjectSpawner::Delete();
}

void DataScene::Update()
{
}

void DataScene::Render()
{
}
