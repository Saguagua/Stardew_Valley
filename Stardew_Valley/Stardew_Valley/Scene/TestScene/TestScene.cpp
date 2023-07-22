#include "framework.h"
#include "TestScene.h"
#include "../../Object/Character/Character.h"

TestScene::TestScene()
{
	_character = make_shared<Character>();
	
	vector<shared_ptr<MapInfo>> v = SaveManager::GetInstance()->GetMapInfos();
	
	_farmmingMap = make_shared<TileMap>(v[0]);
	
	_farmmingMap->SetActive(true);

	_farmmingMap->SetPlayer(_character);

	_character->GetTransform()->SetPos(CENTER);
	
	_character->SetDebug(true);
	_farmmingMap->SetDebug(true);

	_character->Update();
	_farmmingMap->SetCameraRange();
	CAMERA->SetTarget(_character->GetTransform());
	CAMERA->Update();
}

void TestScene::Update()
{
	_farmmingMap->Update();
	
	_character->Update();
}

void TestScene::Render()
{
	_farmmingMap->Render();
	_character->Render();
}