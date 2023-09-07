#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_circle = make_shared<CircleCollider>(50);
	_circle2 = make_shared<CircleCollider>(50);
	_rect = make_shared<RectCollider>(Vector2(50, 50));
	_rect2 = make_shared<RectCollider>(Vector2(50, 50));

	_circle->SetDebug(true);
	_circle2->SetDebug(true);
	_rect->SetDebug(true);
	_rect2->SetDebug(true);

	_circle->SetPos(Vector2(-100, -100));
	_rect2->SetPos(CENTER);
}

void ColliderScene::Update()
{
	_circle->Update();
	_rect2->Update();

	_circle->SetPos(CAMERA->GetWorldMousePos());

	if (KEY_PRESS('Q'))
		_circle->AddAngle(0.01f);

	if (_circle->IsCollision(_rect2))
	{
		_circle->SetColor(XMFLOAT4(1,0,0,1));
	}
	else
	{
		_circle->SetColor(XMFLOAT4(0,1,0,1));
	}
}

void ColliderScene::Render()
{
	_circle->Render();
	_rect2->Render();
}
