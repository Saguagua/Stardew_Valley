#include "framework.h"
#include "../../Data/MapInfo.h"
#include "../../Object/Player/Player.h"
#include "TestScene.h"

TestScene::TestScene()
{
	ObjectSpawner::Create();
	DATA->ReadMaps();
	Player::Create();
	TileMap::Create();

	PLAYER->SetPos(CENTER);
	TILEMAP->ChangeMap(0);


	PLAYER->Update();
	CAMERA->SetTarget(PLAYER->GetTransform());
	CAMERA->Update();
}

TestScene::~TestScene()
{
	TileMap::Delete();
	Player::Delete();
	ObjectSpawner::Delete();
}

void TestScene::Update()
{
	TILEMAP->Update();
	PLAYER->Update();
}

void TestScene::Render()
{
	TILEMAP->Render();
	PLAYER->Render();
}