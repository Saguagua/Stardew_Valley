#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_circle = make_shared<CircleCollider>(50);
	_circle2 = make_shared<CircleCollider>(50);
	_rect = make_shared<RectCollider>(Vector2(50, 50));
	_rect2 = make_shared<RectCollider>(Vector2(50, 50));

	_rect->SetPos(Vector2(-100, -100));

	CAMERA->SetViewPort(WIN_WIDTH, WIN_HEIGHT);
}

void ColliderScene::Update()
{
	_rect->Update();
	_circle2->Update();

	_rect->SetPos(CAMERA->GetWorldMousePos());

	if (_rect->Block(_circle2))
	{
		_rect->SetColor(XMFLOAT4(1,0,0,1));
	}
	else
	{
		_rect->SetColor(XMFLOAT4(0,1,0,1));
	}
}

void ColliderScene::Render()
{
	_rect->Render();
	_circle2->Render();
}
