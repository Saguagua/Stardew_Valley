#include "framework.h"
#include "TestScene.h"

bool TestScene::_bagMode = false; // 위치 이동할 것

TestScene::TestScene()
{
	ObjectSpawner::Create();
	DATA->Load("Test");
	LightManager::Create();
	_player = make_shared<Player>();
	_map = make_shared<TileMap>();

	CAMERA->SetTarget(Player::GetInstance()->GetTransform());
	CAMERA->Update();
}

TestScene::~TestScene()
{
	
	LightManager::Delete();
	ObjectSpawner::Delete();
}

void TestScene::Update()
{
	LightManager::GetInstance()->Update();
	ObjectSpawner::GetInstance()->Update();
	
}

void TestScene::Render()
{
	
	ObjectSpawner::GetInstance()->Render();
	
}

void TestScene::PostRender()
{
	
}
