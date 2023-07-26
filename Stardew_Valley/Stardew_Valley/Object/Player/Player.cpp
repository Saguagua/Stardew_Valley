#include "framework.h"
#include "../../Data/PlayerInfo.h"
#include "Player.h"

Player* Player::_instance = nullptr;

Player::Player()
{
	_col = make_shared<CircleCollider>(15);
	_bodySlot = make_shared<Transform>();
	_body = make_shared<TextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));
	_arm = make_shared<TextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));

	_body->SetCurFrame(Vector2(3, 0));
	_arm->SetCurFrame(Vector2(0, 0));

	_bodySlot->AddPos(Vector2(0, 15));
	_bodySlot->SetParent(_col->GetTransform());

	SetInfos();
	CreateAction();

	_armActions[_armIndex]->Play();
	_bodyActions[_bodyIndex]->Play();
}

void Player::Update()
{
	KeyInput();
	Vector2 pos = _bodySlot->GetWorldPos();
	_col->Update();
	_bodySlot->Update();

	_bodyActions[_bodyIndex]->Update();
	_armActions[_armIndex]->Update();
	_body->SetCurFrame(_bodyActions[_bodyIndex]->GetCurFrame());
	_arm->SetCurFrame(_armActions[_armIndex]->GetCurFrame());
}

void Player::Render()
{
	_bodySlot->Set_World(0);
	_body->Render();
	_arm->Render();
	_col->Render();
}

void Player::KeyInput()
{
	Move();
	Items();
	//Mouse();
}

Vector2 Player::GetWorldPos()
{
	return _col->GetWorldPos();
}

shared_ptr<GameObject> Player::GetSelectedItem()
{
	return _playerInfo->GetItem(_selectedItemIndex);
}

void Player::AddMaxHP(short amount)
{
	_playerInfo->AddMaxHP(amount);
}

void Player::AddMaxStamina(short amount)
{
	_playerInfo->AddMaxStamina(amount);
}

void Player::AddHP(short amount)
{
	_playerInfo->AddHP(amount);
}

void Player::AddStamina(short amount)
{
	_playerInfo->AddStamina(amount);
}

void Player::CreateAction()
{
	vector<Vector2> frontIdleBody;
	frontIdleBody.push_back(Vector2(0, 0));

	vector<Vector2> sideIdleBody;
	sideIdleBody.push_back(Vector2(0, 1));

	vector<Vector2> backIdleBody;
	backIdleBody.push_back(Vector2(0, 2));

	shared_ptr<Action> frontIdleB = make_shared<Action>(frontIdleBody, Action::Type::LOOP, 0.25f);
	shared_ptr<Action> sideIdleB = make_shared<Action>(sideIdleBody, Action::Type::LOOP, 0.25f);
	shared_ptr<Action> backIdleB = make_shared<Action>(backIdleBody, Action::Type::LOOP, 0.25f);

	_bodyActions.push_back(frontIdleB);
	_bodyActions.push_back(sideIdleB);
	_bodyActions.push_back(backIdleB);

	vector<Vector2> frontIdleArm;
	frontIdleArm.push_back(Vector2(6, 0));

	vector<Vector2> sideIdleArm;
	sideIdleArm.push_back(Vector2(6, 1));

	vector<Vector2> backIdleArm;
	backIdleArm.push_back(Vector2(6, 2));


	shared_ptr<Action> frontIdleA = make_shared<Action>(frontIdleArm, Action::Type::LOOP, 0.25f);
	shared_ptr<Action> sideIdleA = make_shared<Action>(sideIdleArm, Action::Type::LOOP, 0.25f);
	shared_ptr<Action> backIdleA = make_shared<Action>(backIdleArm, Action::Type::LOOP, 0.25f);

	_armActions.push_back(frontIdleA);
	_armActions.push_back(sideIdleA);
	_armActions.push_back(backIdleA);

	vector<Vector2> frontRunIndex;
	frontRunIndex.push_back(Vector2(1, 0));
	frontRunIndex.push_back(Vector2(0, 3));
	frontRunIndex.push_back(Vector2(2, 0));
	frontRunIndex.push_back(Vector2(1, 3));

	shared_ptr<Action> frontRunBody = make_shared<Action>(frontRunIndex, Action::Type::LOOP, 0.25f);

	vector<Vector2> sideRunIndex;
	sideRunIndex.push_back(Vector2(5, 1));
	sideRunIndex.push_back(Vector2(2, 3));
	sideRunIndex.push_back(Vector2(5, 2));
	sideRunIndex.push_back(Vector2(3, 3));

	shared_ptr<Action> sideRunBody = make_shared<Action>(sideRunIndex, Action::Type::LOOP, 0.25f);

	vector<Vector2> backRunIndex;
	backRunIndex.push_back(Vector2(1, 2));
	backRunIndex.push_back(Vector2(4, 3));
	backRunIndex.push_back(Vector2(2, 2));
	backRunIndex.push_back(Vector2(5, 3));

	shared_ptr<Action> backRunBody = make_shared<Action>(backRunIndex, Action::Type::LOOP, 0.25f);

	vector<Vector2> frontArmIndex;
	frontArmIndex.push_back(Vector2(7, 0));
	frontArmIndex.push_back(Vector2(6, 3));
	frontArmIndex.push_back(Vector2(8, 0));
	frontArmIndex.push_back(Vector2(7, 3));

	shared_ptr<Action> frontRunArm = make_shared<Action>(frontArmIndex, Action::Type::LOOP, 0.25f);

	vector<Vector2> sideArmIndex;
	sideArmIndex.push_back(Vector2(11, 1));
	sideArmIndex.push_back(Vector2(8, 3));
	sideArmIndex.push_back(Vector2(11, 2));
	sideArmIndex.push_back(Vector2(9, 3));

	shared_ptr<Action> sideRunArm = make_shared<Action>(sideArmIndex, Action::Type::LOOP, 0.25f);

	vector<Vector2> backArmIndex;
	backArmIndex.push_back(Vector2(7, 2));
	backArmIndex.push_back(Vector2(10, 3));
	backArmIndex.push_back(Vector2(8, 2));
	backArmIndex.push_back(Vector2(11, 3));

	shared_ptr<Action> backRunArm = make_shared<Action>(backArmIndex, Action::Type::LOOP, 0.25f);

	_bodyActions.push_back(frontRunBody);
	_bodyActions.push_back(sideRunBody);
	_bodyActions.push_back(backRunBody);

	_armActions.push_back(frontRunArm);
	_armActions.push_back(sideRunArm);
	_armActions.push_back(backRunArm);
}

void Player::SetAction(PlayerAction state)
{
	_armActions[_armIndex]->Stop();
	_bodyActions[_bodyIndex]->Stop();

	_armIndex = state;
	_bodyIndex = state;

	_armActions[_armIndex]->Play();
	_bodyActions[_bodyIndex]->Play();
}

void Player::Move()
{
	if (KEY_PRESS('W'))
	{
		if (_bodyIndex != PlayerAction::BACKRUN)
		{
			SetAction(PlayerAction::BACKRUN);
		}

		_col->AddPos(Vector2(0, 1) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('W'))
	{
		SetAction(PlayerAction::BACKIDLE);
	}

	if (KEY_PRESS('A'))
	{
		if (_bodyIndex != PlayerAction::SIDERUN)
		{
			SetAction(PlayerAction::SIDERUN);
		}
		_col->SetScale(Vector2(-1, 1));

		_col->AddPos(Vector2(-1, 0) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('A'))
	{
		SetAction(PlayerAction::SIDEIDLE);
	}

	if (KEY_PRESS('S'))
	{
		if (_armIndex != PlayerAction::FRONTRUN)
		{
			SetAction(PlayerAction::FRONTRUN);
		}
		_col->AddPos(Vector2(0, -1) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('S'))
	{
		SetAction(PlayerAction::FRONTIDLE);
	}

	if (KEY_PRESS('D'))
	{
		if (_armIndex != PlayerAction::SIDERUN)
		{
			SetAction(PlayerAction::SIDERUN);
		}
		_col->SetScale(Vector2(1, 1));

		_col->AddPos(Vector2(1, 0) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('D'))
	{
		SetAction(PlayerAction::SIDEIDLE);
	}
}

void Player::Items()
{
	if (KEY_DOWN('1'))
	{
		_selectedItemIndex = 0;
	}
	else if (KEY_DOWN('2'))
	{
		_selectedItemIndex = 1;
	}
	else if (KEY_DOWN('3'))
	{
		_selectedItemIndex = 2;
	}
	else if (KEY_DOWN('4'))
	{
		_selectedItemIndex = 3;
	}
	else if (KEY_DOWN('5'))
	{
		_selectedItemIndex = 4;
	}
	else if (KEY_DOWN('6'))
	{
		_selectedItemIndex = 5;
	}
	else if (KEY_DOWN('7'))
	{
		_selectedItemIndex = 6;
	}
	else if (KEY_DOWN('8'))
	{
		_selectedItemIndex = 7;
	}
	else if (KEY_DOWN('9'))
	{
		_selectedItemIndex = 8;
	}
	else if (KEY_DOWN('0'))
	{
		_selectedItemIndex = 9;
	}
}

void Player::Mouse()
{
}
