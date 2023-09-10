#include "framework.h"
#include "Slime.h"

Slime::Slime()
	:Monster("Slime", Vector2(40, 30), 200.0f, MoveType::WALK)
{
	_col->SetDebug(true);
	_bodySlot = make_shared<Transform>();
	_bodySlot->SetParent(_col->GetTransform());

	_eyeSlot = make_shared<Transform>();
	_eyeSlot->SetParent(_col->GetTransform());
	_eyeSlot->SetPos(Vector2(0.0f, -5.0f));

	_body = make_shared<LightTextureRect>(L"Resource/Monsters/Slime.png", Vector2(4, 5), _size);
	_eye = make_shared<LightTextureRect>(L"Resource/Monsters/Slime.png", Vector2(4, 5), _size);
	CreateAction();
}

void Slime::Update()
{
	Monster::Update();

	_eyeSlot->Update();
	_actions[_eyeIndex]->Update();
	_eye->SetCurFrame(_actions[_eyeIndex]->GetCurFrame());

	if (_jumpPower > 0)
	{
		_jumpPower -= DELTA_TIME * 15.0f;
		_col->AddPos(_forceDirection * _jumpPower);
	}
	else if (_stopTimer > 0)
	{
		_stopTimer -= DELTA_TIME;

		if (_stopTimer <= 0)
		{
			_stopTimer = -0.5f;
			_forceDirection.x = rand() % 2 - 1;
			_forceDirection.y = rand() % 2 - 1;
		}
	}
	else
	{
		_stopTimer += DELTA_TIME;
		_col->AddPos(_forceDirection * DELTA_TIME * 200.0f);

		if (_stopTimer > 0)
		{
			_stopTimer = 3.0f;
			_forceDirection.x = 0.0f;
			_forceDirection.y = 0.0f;
		}
	}

	_col->Update();
}

void Slime::Render()
{
	Monster::Render();

	_eyeSlot->Set_World(0);
	_eye->Render();
}


void Slime::CreateAction()
{
#pragma region Idle
	{
		vector<Vector2> indices;
		indices.push_back({ 0, 1 });
		indices.push_back({ 1, 1 });
		indices.push_back({ 2, 1 });
		indices.push_back({ 3, 1 });
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

		move->SetMiddleEvent(std::bind(&Slime::Charging, this));
		move->SetEndEvent(std::bind(&Monster::SetIdle, this));
		_actions.push_back(move);
	}
#pragma endregion

#pragma region Death
	{
		vector<Vector2> indices;
		indices.push_back({ 0, 3 });

		shared_ptr<Action> move = make_shared<Action>(indices, Action::Type::LOOP);

		_actions.push_back(move);
	}
#pragma endregion

#pragma region EyeIdle
	{
		vector<Vector2> indices;
		indices.push_back({ 0, 2 });
		shared_ptr<Action> move = make_shared<Action>(indices, Action::Type::LOOP, 0.5f);

		_actions.push_back(move);
	}
#pragma endregion

#pragma region EyeSURPRISE
	{
		vector<Vector2> indices;
		indices.push_back({ 2, 2 });
		shared_ptr<Action> move = make_shared<Action>(indices, Action::Type::LOOP);

		_actions.push_back(move);
	}
#pragma endregion

#pragma region EyeANGRY
	{
		vector<Vector2> indices;
		indices.push_back({ 3, 2 });
		shared_ptr<Action> move = make_shared<Action>(indices, Action::Type::LOOP);

		_actions.push_back(move);
	}
#pragma endregion

}

void Slime::Charging()
{
	if (_actions[_actionIndex]->GetCurFrame().x == 1)
	{
		_jumpPower = 10.0f;
	}
}

void Slime::Initialize()
{
	_actions[SlimeAction::IDLE]->Play();
	_actions[SlimeAction::EYEIDLE]->Play();

	_eyeIndex = SlimeAction::EYEIDLE;
	_actionIndex = MonsterAction::IDLE;

	_hp = 5;
	_isActive = true;
}

void Slime::Detect(shared_ptr<PlayerFight> player)
{
	if (_col->IsCollision(player->GetCollider()) && !player->IsUntouchable())
	{
		player->AddHP(-5);
		player->StartUntouchable(1.0f);
	}
	
	if (_jumpPower <= 0)
	{
		if (_detectArea->IsCollision(player->GetCollider()))
		{
			_chargeCount += DELTA_TIME;

			if (_chargeCount > 1.5f)
			{
				_chargeCount = 0.0f;
				_forceDirection = (player->GetWorldPos() - _col->GetWorldPos()).Normalize();

				SetAction(MonsterAction::MOVE);

				_stopTimer = 3.0f;
			}
		}
		else
		{
			_chargeCount = 0.0f;
		}
	}
	
}

