#include "framework.h"
#include "Slime.h"

Slime::Slime()
	:Creature("Slime", Vector2(50, 50))
{
	_col->SetDebug(true);
	_bodySlot = make_shared<Transform>();
	_bodySlot->SetParent(_col->GetTransform());
	_col->SetPos(CENTER);
	_body = make_shared<LightTextureRect>(L"Resource/Monsters/Slime.png", Vector2(4, 5), _size);
	CreateAction();
	_actions[SlimeAction::IDLE]->Play();
}

void Slime::Update()
{
	Creature::Update();
}

void Slime::CreateAction()
{
#pragma region Idle
	{
		vector<Vector2> indices;
		indices.push_back({0, 1});
		indices.push_back({1, 1});
		indices.push_back({2, 1});
		indices.push_back({3, 1});
		shared_ptr<Action> idle = make_shared<Action>(indices, Action::Type::LOOP);

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
		shared_ptr<Action> move = make_shared<Action>(indices, Action::Type::LOOP);

		_actions.push_back(move);
	}
#pragma endregion
}
