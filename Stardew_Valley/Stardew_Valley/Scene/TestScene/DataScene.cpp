#include "framework.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Tile/Tile.h"
#include "DataScene.h"

DataScene::DataScene()
{
	ObjectSpawner::Create();
	LightManager::Create();
	DATA->Load("Test");
	PlayerUI::Create();
	_player = make_shared<Player>();
	CAMERA->SetTarget(DATA->GetPlayerInfo()->GetTransform());
}

DataScene::~DataScene()
{
	ObjectSpawner::Delete();
	PlayerUI::Delete();
	LightManager::Delete();
}

void DataScene::Update()
{
	LightManager::GetInstance()->Update();
	_player->Update();
	PlayerUI::GetInstance()->Update();
	DATA->GetSelectedItem()->KeyInput();
}

void DataScene::Render()
{
	_player->Render();
}

void DataScene::PostRender()
{
	PlayerUI::GetInstance()->PostRender();
}
