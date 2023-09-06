#include "framework.h"
#include "Monster.h"

Monster::Monster(string name, Vector2 size, float areaSize)
	:Creature(name, size)
{
	_detectArea = make_shared<CircleCollider>(areaSize);
	_detectArea->SetDebug(true);

	_detectArea->SetParent(_col->GetTransform());
}

void Monster::Move(Vector2 direction)
{
	_forceDirection = direction;
	SetAction(MonsterAction::MOVE);
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

void Monster::SetIdle()
{
	SetAction(MonsterAction::IDLE);
}
