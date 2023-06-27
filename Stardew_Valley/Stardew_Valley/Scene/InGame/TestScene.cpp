#include "framework.h"
#include "TestScene.h"
#include "../../Object/BagicObj/TileMap.h"
#include "../../Framework/Collision/RectCollider.h"
#include "../../Framework/Collision/CircleCollider.h"

TestScene::TestScene()
{
	_tileMap = make_shared<TileMap>(Vector2(50, 50));
	_circle = make_shared<CircleCollider>(30);
	_circle->SetPos(CENTER);
	_circle->Update();

	CAMERA->SetTarget(_circle->GetTransform());
	CAMERA->SetLeftBottom(CENTER);
	CAMERA->SetRightTop(Vector2(2500 - CENTER.x, 2500 - CENTER.y));

}

void TestScene::Update()
{
	if (KEY_PRESS('D'))
		_circle->AddPos(Vector2(1,0) * DELTA_TIME * 100.0f);
	_tileMap->Update();
	_circle->Update();
}

void TestScene::Render()
{
	_tileMap->Render();
	_circle->Render();
}