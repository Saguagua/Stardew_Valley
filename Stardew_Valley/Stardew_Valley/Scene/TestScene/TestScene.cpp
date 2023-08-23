#include "framework.h"
#include "TestScene.h"

bool TestScene::_bagMode = false; // 위치 이동할 것

TestScene::TestScene()
{
	ObjectSpawner::Create();
	DATA->Load("Test");
	LightManager::Create();
	TileMap::Create();
	Player::Create();
	PlayerUI::Create();

	CAMERA->SetTarget(Player::GetInstance()->GetTransform());
	CAMERA->Update();
}

TestScene::~TestScene()
{
	PlayerUI::Delete();
	Player::Delete();
	TileMap::Delete();
	LightManager::Delete();
	ObjectSpawner::Delete();
}

void TestScene::Update()
{
	LightManager::GetInstance()->Update();
	ObjectSpawner::GetInstance()->Update();
	PlayerUI::GetInstance()->Update();

	Player::GetInstance()->Update();
	TileMap::GetInstance()->Update();
}

void TestScene::Render()
{
	TileMap::GetInstance()->Render();
	ObjectSpawner::GetInstance()->Render();
	Player::GetInstance()->Render();
}

void TestScene::PostRender()
{
	PlayerUI::GetInstance()->PostRender();
}
