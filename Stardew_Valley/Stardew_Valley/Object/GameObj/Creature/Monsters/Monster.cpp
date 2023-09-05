#include "framework.h"
#include "Monster.h"

Monster::Monster(string name, Vector2 size)
	:Creature(name, size)
{
	_detectArea = make_shared<CircleCollider>(200);
	_detectArea->SetDebug(true);

	_detectArea->SetParent(_col->GetTransform());
}

void Monster::Move(Vector2 direction)
{
	_direction = direction;
	_moveTimer = 0.5f;
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

	if (_moveTimer > 0)
	{
		_moveTimer -= DELTA_TIME;
		_col->AddPos(_direction * DELTA_TIME * _speed);

		if (_moveTimer <= 0)
		{
			_stopTimer = 5.0f;
			_direction.x = 0.0f;
			_direction.y = 0.0f;
			SetAction(MonsterAction::IDLE);
		}
	}
	else
	{
		_stopTimer -= DELTA_TIME;
		if (_stopTimer <= 0)
		{
			_moveTimer = 1.0f;
			_direction.x = rand() % 3 - 1;
			_direction.y = rand() % 3 - 1;
			SetAction(MonsterAction::MOVE);
		}
	}
}
