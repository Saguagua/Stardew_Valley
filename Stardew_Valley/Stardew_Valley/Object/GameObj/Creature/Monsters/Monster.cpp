#include "framework.h"
#include "Monster.h"

Monster::Monster(string name, Vector2 size, float areaSize, MoveType type)
	:Creature(name, size), _type(type)
{
	_detectArea = make_shared<CircleCollider>(areaSize);

	_detectArea->SetParent(_col->GetTransform());
}

void Monster::Render()
{
	Creature::Render();
	_detectArea->Render();
}

void Monster::Update()
{
	Creature::Update();
	_detectArea->Update();
}

void Monster::AddHP(short cost)
{
	_hp += cost;

	if (_hp <= 0)
	{
		_isActive = false;
		OBJECT_SPAWNER->ActiveDropItem(_name, _col->GetWorldPos());
		EFFECT->ActiveEffect(_col->GetWorldPos(), 1);
	}
}

void Monster::SetIdle()
{
	SetAction(MonsterAction::IDLE);
}

void Monster::Spawn(Vector2 pos)
{
	_col->SetPos(pos);
	Initialize();
}
