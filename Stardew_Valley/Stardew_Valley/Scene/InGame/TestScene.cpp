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
	CAMERA->SetLeftBottom(Vector2(-735 + WIN_WIDTH / 2, -735 + WIN_HEIGHT / 2));
	CAMERA->SetRightTop(Vector2(735 - WIN_WIDTH / 2, 735 - WIN_HEIGHT / 2));
}

void TestScene::Update()
{
	_tileMap->Update();
	_character->Update();
	vector<vector<shared_ptr<TileMap::TileInfo>>> v = _tileMap->GetInfo();
	Vector2 cWorldPos = _character->GetTransform()->GetWorldPos();
	Vector2 worldIndex = _tileMap->GetWorldIndex(cWorldPos);
	v[worldIndex.y][worldIndex.x]->curClip.x = 1;
}

void TestScene::Render()
{
	_tileMap->Render();
	_character->Render();
}