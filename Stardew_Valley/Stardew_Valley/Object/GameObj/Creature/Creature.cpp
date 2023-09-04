#include "framework.h"
#include "Creature.h"

Creature::Creature(string name, Vector2 size)
	:_name(name), _size(size)
{
	_col = make_shared<RectCollider>(_size);
}

void Creature::Update()
{
	if (!_isActive)
		return;

	_col->Update();
	_bodySlot->Update();
	_actions[_actionIndex]->Update();
	_body->SetCurFrame(_actions[_actionIndex]->GetCurFrame());
}

void Creature::Render()
{
	if (!_isActive)
		return;

	_bodySlot->Set_World(0);
	_body->Render();
	_col->Render();
}

void Creature::AddHP(short cost)
{
	_hp += cost;
}

void Creature::SetAction(int state)
{
	state += _dir;

	if (_actionIndex == state)
		return;

	_actions[_actionIndex]->Reset();

	_actionIndex = state;

	_actions[_actionIndex]->Play();
}

void Creature::SetDirection(Vector2 pos)
{
	Vector2 dir = pos - _col->GetWorldPos();

	if (abs(dir.x) > abs(dir.y))
	{
		if (dir.x < 0)
			_col->SetScale(Vector2(-1, 1));
		else
			_col->SetScale(Vector2(1, 1));

		_dir = SIDE;
	}
	else
	{
		if (dir.y < 0)
			_dir = FRONT;
		else
			_dir = BACK;
	}
}

void Creature::SetPause(bool val)
{
	_actions[_actionIndex]->Pause(val);
	_freeze = val;
}
