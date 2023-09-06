#include "framework.h"
#include "Bat.h"

Bat::Bat()
	:Monster("Bat", Vector2(30, 30), 500.0f)
{
	_col->SetDebug(true);
	_bodySlot = make_shared<Transform>();
	_bodySlot->SetParent(_col->GetTransform());

	_body = make_shared<LightTextureRect>(L"Resource/Monsters/Bat.png", Vector2(4, 2), _size);
	CreateAction();

	_actions[MonsterAction::IDLE]->Play();
}

Bat::~Bat()
{
}

void Bat::Render()
{
	Monster::Render();
}

void Bat::Update()
{
	Monster::Update();

	if (_power > 0)
	{
		_power -= DELTA_TIME * 1.0f;
		_col->AddPos(_direction * _power);
	}
}

void Bat::Move(Vector2 dir)
{

	Monster::Move(dir);

	_power = 5.0f;
}

void Bat::CreateAction()
{

#pragma region Idle
	{
		vector<Vector2> indices;
		indices.push_back({ 0, 1 });
		shared_ptr<Action> idle = make_shared<Action>(indices, Action::Type::LOOP, 0.3f);

		_actions.push_back(idle);
	}
#pragma endregion

#pragma region Move
	{
		vector<Vector2> indices;
		indices.push_back({ 0, 0 });
		indices.push_back({ 1, 0 });
		indices.push_back({ 2, 0 });
		indices.push_back({ 3, 0 });
		shared_ptr<Action> move = make_shared<Action>(indices, Action::Type::END, 0.3f);

		move->SetEndEvent(std::bind(&Monster::SetIdle, this));
		_actions.push_back(move);
	}
#pragma endregion

#pragma region Death
	{
		vector<Vector2> indices;
		indices.push_back({ 1, 1 });

		shared_ptr<Action> move = make_shared<Action>(indices, Action::Type::LOOP);

		_actions.push_back(move);
	}
#pragma endregion
}
