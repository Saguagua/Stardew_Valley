#include "framework.h"
#include "Character.h"

Character::Character()
{
	_collider = make_shared<CircleCollider>(10);
	_quadSlot = make_shared<Transform>();
	_quad = make_shared<TextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(30, 50));
	
	_quadSlot->AddPos(Vector2(0, 15));
	_quadSlot->SetParent(_collider->GetTransform());
}

void Character::Update()
{
	KeyInput();
	Vector2 pos = _quadSlot->GetWorldPos();
	_collider->Update();
	_quadSlot->Update();
	_quad->Update();
}

void Character::Render()
{
	_quadSlot->Set_World(0);
	_quad->Render();
	_collider->Render();
}

void Character::KeyInput()
{
	if (KEY_PRESS('W'))
	{
		_collider->AddPos(Vector2(0, 1) * DELTA_TIME * 200);
	}
	if (KEY_PRESS('A'))
	{
		_collider->AddPos(Vector2(-1, 0) * DELTA_TIME * 200);
	}
	if (KEY_PRESS('S'))
	{
		_collider->AddPos(Vector2(0, -1) * DELTA_TIME * 200);
	}
	if (KEY_PRESS('D'))
	{
		_collider->AddPos(Vector2(1, 0) * DELTA_TIME * 200);
	}
}
