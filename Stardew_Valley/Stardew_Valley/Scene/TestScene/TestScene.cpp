#include "framework.h"
#include "TestScene.h"
#include "../../Object/Player/Player.h"

TestScene::TestScene()
{
	_player = make_shared<Player>();
	vector<shared_ptr<MapInfo>> v = DATA->GetMapInfos();
	
	_farmmingMap = make_shared<TileMap>(v[0]);
	
	_farmmingMap->SetActive(true);

	_farmmingMap->SetPlayer(_player);

	_player->GetTransform()->SetPos(CENTER);
	
	//_farmmingMap->SetDebug(true);
	_player->Update();
	_farmmingMap->SetCameraRange();
	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->Update();
}

void TestScene::Update()
{
	_farmmingMap->Update();
	_player->Update();
}

void TestScene::Render()
{
	_farmmingMap->Render();
	_player->Render();
}