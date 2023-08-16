#include "framework.h"
#include "../../Data/MapInfo.h"
#include "../../Object/Player/Player.h"
#include "../../Object/BasicObj/XMLRect.h"
#include "TestScene.h"

TestScene::TestScene()
{
	ObjectSpawner::Create();
	DATA->Load("Test");
	ObjectSpawner::GetInstance()->SetPlayerInfo(); // 구조 바뀌면 삭제
	LightManager::Create();
	TileMap::Create();
	
	PlayerUI::Create();
	_player = make_shared<Player>();

	TileMap::GetInstance()->ChangeMap(0);

	_player->Update();
	CAMERA->SetTarget(DATA->GetPlayerInfo()->GetTransform());
	CAMERA->Update();
}

TestScene::~TestScene()
{
	PlayerUI::Delete();
	LightManager::Delete();
	ObjectSpawner::Delete();
}

void TestScene::Update()
{
	LightManager::GetInstance()->Update();
	ObjectSpawner::GetInstance()->Update();
	PlayerUI::GetInstance()->Update();

	TileMap::GetInstance()->Update();
	_player->Update();


	auto item = DATA->GetSelectedItem();
	DATA->GetSelectedItem()->KeyInput();
}

void TestScene::Render()
{
	TileMap::GetInstance()->Render();
	ObjectSpawner::GetInstance()->Render();
	_player->Render();
}

void TestScene::PostRender()
{
	PlayerUI::GetInstance()->PostRender();
}
