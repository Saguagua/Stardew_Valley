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
	
	PlayerUI::Create();

	_player = make_shared<Player>();
	_map = make_shared<TileMap>();

	_map->ChangeMap(0);

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
	_map->Update();
	ObjectSpawner::GetInstance()->Update();
	_player->Update();
	PlayerUI::GetInstance()->Update();
}

void TestScene::Render()
{
	_map->Render();
	ObjectSpawner::GetInstance()->Render();
	_player->Render();
}

void TestScene::PostRender()
{
	PlayerUI::GetInstance()->PostRender();
}
