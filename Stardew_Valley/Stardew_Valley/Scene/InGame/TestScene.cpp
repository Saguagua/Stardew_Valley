#include "framework.h"
#include "TestScene.h"
#include "../../Object/BagicObj/TileMap.h"
#include "../../Framework/Collision/RectCollider.h"
#include "../../Framework/Collision/CircleCollider.h"
#include "../../Object/Character/Character.h"

TestScene::TestScene()
{
	_tileMap = make_shared<TileMap>(Vector2(50, 50));
	_character = make_shared<Character>();
	_character->GetTransform()->SetPos(Vector2(0,0));

	CAMERA->SetViewPort(WIN_WIDTH, WIN_HEIGHT);

	CAMERA->SetTarget(_character->GetTransform());
	CAMERA->SetLeftBottom(Vector2(-1250 + WIN_WIDTH / 2, -1250 + WIN_HEIGHT / 2));
	CAMERA->SetRightTop(Vector2(1250 - WIN_WIDTH / 2, 1250 - WIN_HEIGHT / 2));
}

void TestScene::Update()
{
	_tileMap->Update();
	_character->Update();
}

void TestScene::Render()
{
	_tileMap->Render();
	_character->Render();
}