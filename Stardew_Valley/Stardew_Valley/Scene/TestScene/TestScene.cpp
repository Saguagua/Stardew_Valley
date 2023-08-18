#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	ObjectSpawner::Create();
	DATA->Load("Test");
	LightManager::Create();
	TileMap::Create();
	Player::Create();
	PlayerUI::Create();
	

	TileMap::GetInstance()->ChangeMap(0);

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

	TileMap::GetInstance()->Update();
	Player::GetInstance()->Update();


	//DATA->GetSelectedItem()->KeyInput();
}

void TestScene::Render()
{
	TileMap::GetInstance()->Render();
	ObjectSpawner::GetInstance()->Render();
	Player::GetInstance()->Render();
}

void TestScene::PostRender()
{
	//PlayerUI::GetInstance()->PostRender();
}
