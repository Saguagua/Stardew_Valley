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
	Vector2 mainWorldPos = _character->GetTransform()->GetWorldPos();
	vector<vector<shared_ptr<TileMap::TileInfo>>> v = _tileMap->GetInfo();
	Vector2 worldIndex = _tileMap->GetWorldIndex(mainWorldPos);

	v[worldIndex.y][worldIndex.x]->curClip.x = 1;

	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 mouse = CAMERA->GetWorldMousePos();
		Vector2 target = mouse - mainWorldPos;

		float angle = target.Angle() * 57.2958;

		if (angle > -25.0f && angle <= 25.0f)
		{
			v[worldIndex.y][worldIndex.x+1]->curClip.x++;
		}
		else if (angle > 25.0f && angle <= 70.0f)
		{
			v[worldIndex.y + 1][worldIndex.x + 1]->curClip.x++;
		}
		else if (angle > 70.0f && angle <= 115.0f)
		{
			v[worldIndex.y + 1][worldIndex.x]->curClip.x++;
		}
		else if (angle > 115.0f && angle < 160.0f)
		{
			v[worldIndex.y + 1][worldIndex.x - 1]->curClip.x++;
		}
		else if (angle > -70.0f && angle <= -25.0f)
		{
			v[worldIndex.y - 1][worldIndex.x + 1]->curClip.x++;
		}
		else if (angle > -115.0f && angle <= -70.0f)
		{
			v[worldIndex.y - 1][worldIndex.x]->curClip.x++;
		}
		else if (angle > -160.0f && angle <= -25.0f)
		{
			v[worldIndex.y - 1][worldIndex.x - 1]->curClip.x++;
		}
		else
		{
			v[worldIndex.y][worldIndex.x - 1]->curClip.x++;
		}
	}
	
}

void TestScene::Render()
{
	_tileMap->Render();
	_character->Render();
}