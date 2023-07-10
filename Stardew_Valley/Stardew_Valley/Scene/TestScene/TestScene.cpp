#include "framework.h"
#include "TestScene.h"
#include "../../Object/Character/Character.h"

TestScene::TestScene()
{
	_character = make_shared<Character>();
	_beachMap = make_shared<TileMap>(L"Resource/Tile/spring_beach.png", Vector2(50, 50), Vector2(30, 30) ,_character);
	_beachMap->SetActive(true);
}

void TestScene::Update()
{
	_beachMap->Update();
	_character->Update();
}

void TestScene::Render()
{
	_beachMap->Render();
	_character->Render();
}