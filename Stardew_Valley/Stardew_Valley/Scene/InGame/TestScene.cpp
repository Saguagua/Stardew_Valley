#include "framework.h"
#include "TestScene.h"
#include "../../Object/BagicObj/TileMap.h"
#include "../../Framework/Collision/RectCollider.h"
#include "../../Framework/Collision/CircleCollider.h"

TestScene::TestScene()
{
	_tileMap = make_shared<TileMap>(Vector2(100, 100));
	_circle = make_shared<CircleCollider>(100);
	_rect = make_shared<RectCollider>(Vector2(100, 100));
	_circle->SetPos(CENTER);
}

void TestScene::Update()
{
	//_tileMap->Update();
	_circle->Update();
	_rect->Update();
}

void TestScene::Render()
{
	//_tileMap->Render();
	_circle->Render();
	_rect->Render();
}