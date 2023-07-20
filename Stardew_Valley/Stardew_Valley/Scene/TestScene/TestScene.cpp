#include "framework.h"
#include "TestScene.h"
#include "../../Object/Character/Character.h"

TestScene::TestScene()
{
	_character = make_shared<Character>();
	
	vector<shared_ptr<MapInfo>> v = SaveManager::GetInstance()->GetMapInfos();
	
	_farmmingMap = make_shared<TileMap>(v[0]);
	_beachMap = make_shared<TileMap>(v[1]);
	_beachMap->SetActive(true);
	_farmmingMap->SetActive(false);

	_farmmingMap->SetPlayer(_character);
	_beachMap->SetPlayer(_character);
	_beachMap->SetDebug(true);

	_character->GetTransform()->SetPos(CENTER + Vector2(0, 100));
	
	_character->SetDebug(true);
	_character->Update();
	_beachMap->SetCameraRange();
	CAMERA->SetTarget(_character->GetTransform());
	CAMERA->Update();
}

void TestScene::Update()
{
	_farmmingMap->Update();
	_beachMap->Update();
	_character->Update();
	
}

void TestScene::Render()
{
	_farmmingMap->Render();
	_beachMap->Render();
	_character->Render();
	
}