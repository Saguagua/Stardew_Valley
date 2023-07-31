#include "framework.h"
#include "../../Data/MapInfo.h"
#include "../../Object/Player/Player.h"
#include "../../Object/BasicObj/XMLRect.h"
#include "TestScene.h"

TestScene::TestScene()
{
	ObjectSpawner::Create();
	DATA->Load("Test");
	Player::Create();
	TileMap::Create();
	PlayerUI::Create();

	PLAYER->SetPos(CENTER);
	TILEMAP->ChangeMap(0);

	PLAYER->Update();
	CAMERA->SetTarget(PLAYER->GetTransform());
	CAMERA->Update();
}

TestScene::~TestScene()
{
	PlayerUI::Delete();
	TileMap::Delete();
	Player::Delete();
	ObjectSpawner::Delete();
}

void TestScene::Update()
{
	TILEMAP->Update();
	PLAYER->Update();
	PlayerUI::GetInstance()->Update();
}

void TestScene::Render()
{
	TILEMAP->Render();
	PLAYER->Render();
}

void TestScene::PostRender()
{
	PlayerUI::GetInstance()->PostRender();
}
