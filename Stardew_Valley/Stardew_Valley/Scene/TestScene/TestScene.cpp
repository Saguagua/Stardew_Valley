#include "framework.h"
#include "TestScene.h"
#include "../../Object/BagicObj/TileMap.h"
#include "../../Framework/Collision/RectCollider.h"
#include "../../Framework/Collision/CircleCollider.h"
#include "../../Object/Character/Character.h"

TestScene::TestScene()
{
	_character = make_shared<Character>();
	_beachMap = make_shared<TileMap>(Vector2(50, 50), L"Resource/Tile/spring_beach.png", _character);

	CAMERA->SetViewPort(WIN_WIDTH, WIN_HEIGHT);
	CAMERA->SetTarget(_character->GetTransform());
	_beachMap->SetCameraRange();
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