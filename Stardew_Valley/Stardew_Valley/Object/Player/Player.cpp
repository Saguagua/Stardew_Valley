#include "framework.h"
#include "Player.h"

Player::Player()
{
	_collider = make_shared<CircleCollider>(15);
	_bodySlot = make_shared<Transform>();
	_body = make_shared<TextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));
	_arm = make_shared<TextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));

	_body->SetCurFrame(Vector2(3, 0));
	_arm->SetCurFrame(Vector2(0, 0));

	_bodySlot->AddPos(Vector2(-5, 0));
	_bodySlot->SetParent(_collider->GetTransform());

	CreateAction();

	_armActions[_armIndex]->Play();
	_bodyActions[_bodyIndex]->Play();
}

void Player::Update()
{
	KeyInput();
	Vector2 pos = _bodySlot->GetWorldPos();
	_collider->Update();
	_bodySlot->Update();

	_bodyActions[_bodyIndex]->Update();
	_armActions[_armIndex]->Update();
	_body->SetCurFrame(_bodyActions[_bodyIndex]->GetCurFrame());
	_arm->SetCurFrame(_armActions[_armIndex]->GetCurFrame());
	_body->Update();
	_arm->Update();
}

void Player::Render()
{
	_bodySlot->Set_World(0);
	_body->Render();
	_arm->Render();
	_collider->Render();
}

void Player::KeyInput()
{
	if (KEY_PRESS('W'))
	{
		if (_armIndex != 2)
		{
			_armActions[_armIndex]->Stop();
			_bodyActions[_bodyIndex]->Stop();

			_armIndex = 2;
			_bodyIndex = 2;


			_armActions[_armIndex]->Play();
			_bodyActions[_bodyIndex]->Play();
		}

		_collider->AddPos(Vector2(0, 1) * DELTA_TIME * SPEED);
	}
	if (KEY_PRESS('A'))
	{
		if (_armIndex != 1)
		{
			_armActions[_armIndex]->Stop();
			_bodyActions[_bodyIndex]->Stop();

			_armIndex = 1;
			_bodyIndex = 1;

			_armActions[_armIndex]->Play();
			_bodyActions[_bodyIndex]->Play();
		}
		_collider->SetScale(Vector2(-1, 1));

		_collider->AddPos(Vector2(-1, 0) * DELTA_TIME * SPEED);
	}
	if (KEY_PRESS('S'))
	{
		if (_armIndex != 0)
		{
			_armActions[_armIndex]->Stop();
			_bodyActions[_bodyIndex]->Stop();

			_armIndex = 0;
			_bodyIndex = 0;

			_armActions[_armIndex]->Play();
			_bodyActions[_bodyIndex]->Play();
		}
		_collider->AddPos(Vector2(0, -1) * DELTA_TIME * SPEED);
	}
	if (KEY_PRESS('D'))
	{
		if (_armIndex != 1)
		{
			_armActions[_armIndex]->Stop();
			_bodyActions[_bodyIndex]->Stop();

			_armIndex = 1;
			_bodyIndex = 1;

			_armActions[_armIndex]->Play();
			_bodyActions[_bodyIndex]->Play();
		}
		_collider->SetScale(Vector2(1, 1));

		_collider->AddPos(Vector2(1, 0) * DELTA_TIME * SPEED);
	}
}

Vector2 Player::GetWorldPos()
{
	return _collider->GetWorldPos();
}

void Player::CreateAction()
{
	/*shared_ptr<Action> frontRunBody = make_shared<Action>(1, 2, 0, Action::Type::LOOP, 0.25f);
	shared_ptr<Action> sideRunBody = make_shared<Action>(1, 2, 1, Action::Type::LOOP, 0.25f);
	shared_ptr<Action> upRunBody = make_shared<Action>(1, 2, 2, Action::Type::LOOP, 0.25f);
	shared_ptr<Action> frontRunArm = make_shared<Action>(6, 8, 0, Action::Type::LOOP, 0.25f);
	shared_ptr<Action> sideRunArm = make_shared<Action>(6, 8, 1, Action::Type::LOOP, 0.25f);
	shared_ptr<Action> upRunArm = make_shared<Action>(6, 8, 2, Action::Type::LOOP, 0.25f);

	_bodyActions.push_back(frontRunBody);
	_bodyActions.push_back(sideRunBody);
	_bodyActions.push_back(upRunBody);

	_armActions.push_back(frontRunArm);
	_armActions.push_back(sideRunArm);
	_armActions.push_back(upRunArm);*/
}
