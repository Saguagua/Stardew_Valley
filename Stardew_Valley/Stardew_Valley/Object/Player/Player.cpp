#include "framework.h"
#include "PlayerSubscribe.h"
#include "Player.h"

Player* Player::_instance = nullptr;

Player::Player()
{
	_col = make_shared<RectCollider>(Vector2(20, 20));
	_magnatic = make_shared<CircleCollider>(50);
	_col->SetDebug(true);
	_magnatic->SetDebug(true);

	_bodySlot = make_shared<Transform>();
	_itemSlot = make_shared<Transform>();

	_body = make_shared<LightTextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));
	_arm = make_shared<LightTextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));
	_obj = make_shared<Sprite>(L"Resource/XMLResource.png", "BLANK", Vector2(30, 30));

	_body->SetCurFrame(Vector2(3, 0));
	_arm->SetCurFrame(Vector2(0, 0));

	_magnatic->SetParent(_col->GetTransform());
	_bodySlot->AddPos(Vector2(0, 20));
	_bodySlot->SetParent(_col->GetTransform());
	_itemSlot->AddPos(Vector2(0, 30));
	_itemSlot->SetParent(_bodySlot);
	CreateAction();

	_armActions[_armIndex]->Play();
	_bodyActions[_bodyIndex]->Play();
}

void Player::Update()
{
	KeyInput();
	_col->Update();
	_magnatic->Update();
	_bodySlot->Update();
	_itemSlot->Update();
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

	_itemSlot->Set_World(0);
	_obj->Render();
	_col->Render();
	_magnatic->Render();
}

shared_ptr<PlayerInfo> Player::RequestSubscribe(PlayerSubscribe* subscriber)
{
	_subscribers.push_back(subscriber);

	return _playerInfo;
}

void Player::SendToSubscribers(int type)
{
	for (auto subscriber : _subscribers)
	{
		if (subscriber->_type == type)
			subscriber->UpdateInfo();
	}
}

bool Player::AddMaxHP(short cost)
{
	return false;
}

bool Player::AddMaxStamina(short cost)
{
	return false;
}

bool Player::AddHP(short cost)
{
	float maxHP = _playerInfo->GetMaxHP();
	float hp = _playerInfo->GetHP();

	hp += cost;

	if (hp <= 0)
		_playerInfo->SetState(PlayerState::DEAD);

	float ratio = hp / maxHP;
	PlayerUI::GetInstance()->SetHP(ratio);
	_playerInfo->SetHP(hp);

	return !(_playerInfo->GetState() & PlayerState::DEAD);
}

bool Player::AddStamina(short cost)
{
	float maxStamina = _playerInfo->GetMaxStamina();
	float stamina = _playerInfo->GetStamina();

	stamina += cost;

	if (stamina <= 0)
		_playerInfo->SetState(PlayerState::DEAD);

	float ratio = stamina / maxStamina;
	PlayerUI::GetInstance()->SetStamina(ratio);
	_playerInfo->SetStamina(stamina);

	return !(_playerInfo->GetState() & PlayerState::DEAD);
}

void Player::CancelSubscribe(PlayerSubscribe* sub)
{
	for (auto subscriber : _subscribers)
	{
		if (subscriber == sub)
			_subscribers.remove(sub);
	}
}

void Player::KeyInput()
{
	if (_playerInfo->GetState() & (PlayerState::DEAD | PlayerState::IMMOVEABLE))
		return;

	Move();
	Items();
	Mouse();
}

void Player::SetSelectedItemIndex(int index)
{
	_playerInfo->SetSelectedIndex(index);
	auto item = _playerInfo->GetSelectedItem();
	int type = item->GetType();
	int& state = _playerInfo->GetStateRef();
	int armIndex = _armIndex;

	if (type == Item::Type::NONE ||
		type == Item::Type::EATABLE ||
		type == Item::Type::FERTILIZER ||
		type == Item::Type::SEED)
	{
		state |= PlayerState::HOLDING;
		_obj->ChangePicture(item->GetName(), item->GetIndex());
		armIndex = PlayerAction::HOLD;
	}
	else
	{
		state &= ~(PlayerState::HOLDING);
		_obj->ChangePicture("BLANK");
		if (state != PlayerState::RUN)
			armIndex = PlayerAction::IDLE;
		else
			armIndex = PlayerAction::RUN;
	}
	
	SetArmAction(armIndex);
}

void Player::CreateAction()
{
#pragma region Idle
	{
		vector<Vector2> frontIdleBody;
		frontIdleBody.push_back(Vector2(0, 0));

		vector<Vector2> sideIdleBody;
		sideIdleBody.push_back(Vector2(0, 1));

		vector<Vector2> backIdleBody;
		backIdleBody.push_back(Vector2(0, 2));

		shared_ptr<Action> frontIdleB = make_shared<Action>(frontIdleBody, Action::Type::LOOP);
		shared_ptr<Action> sideIdleB = make_shared<Action>(sideIdleBody, Action::Type::LOOP);
		shared_ptr<Action> backIdleB = make_shared<Action>(backIdleBody, Action::Type::LOOP);

		_bodyActions.push_back(frontIdleB);
		_bodyActions.push_back(sideIdleB);
		_bodyActions.push_back(backIdleB);

		vector<Vector2> frontIdleArm;
		frontIdleArm.push_back(Vector2(6, 0));

		vector<Vector2> sideIdleArm;
		sideIdleArm.push_back(Vector2(6, 1));

		vector<Vector2> backIdleArm;
		backIdleArm.push_back(Vector2(6, 2));


		shared_ptr<Action> frontIdleA = make_shared<Action>(frontIdleArm, Action::Type::LOOP, 0.1f);
		shared_ptr<Action> sideIdleA = make_shared<Action>(sideIdleArm, Action::Type::LOOP, 0.1f);
		shared_ptr<Action> backIdleA = make_shared<Action>(backIdleArm, Action::Type::LOOP, 0.1f);

		_armActions.push_back(frontIdleA);
		_armActions.push_back(sideIdleA);
		_armActions.push_back(backIdleA);
	}
#pragma endregion

#pragma region Run
	{
		vector<Vector2> frontIndex;
		frontIndex.push_back(Vector2(1, 0));
		frontIndex.push_back(Vector2(0, 3));
		frontIndex.push_back(Vector2(2, 0));
		frontIndex.push_back(Vector2(1, 3));

		shared_ptr<Action> frontBody = make_shared<Action>(frontIndex, Action::Type::LOOP, 0.1f);

		vector<Vector2> sideIndex;
		sideIndex.push_back(Vector2(2, 3));
		sideIndex.push_back(Vector2(5, 1));
		sideIndex.push_back(Vector2(3, 3));
		sideIndex.push_back(Vector2(5, 2));

		shared_ptr<Action> sideBody = make_shared<Action>(sideIndex, Action::Type::LOOP, 0.1f);

		vector<Vector2> backIndex;
		backIndex.push_back(Vector2(4, 3));
		backIndex.push_back(Vector2(1, 2));
		backIndex.push_back(Vector2(5, 3));
		backIndex.push_back(Vector2(2, 2));

		shared_ptr<Action> backBody = make_shared<Action>(backIndex, Action::Type::LOOP, 0.1f);

		vector<Vector2> frontArmIndex;
		frontArmIndex.push_back(Vector2(7, 0));
		frontArmIndex.push_back(Vector2(6, 3));
		frontArmIndex.push_back(Vector2(8, 0));
		frontArmIndex.push_back(Vector2(7, 3));

		shared_ptr<Action> frontArm = make_shared<Action>(frontArmIndex, Action::Type::LOOP, 0.1f);

		vector<Vector2> sideArmIndex;
		sideArmIndex.push_back(Vector2(11, 1));
		sideArmIndex.push_back(Vector2(8, 3));
		sideArmIndex.push_back(Vector2(11, 2));
		sideArmIndex.push_back(Vector2(9, 3));

		shared_ptr<Action> sideArm = make_shared<Action>(sideArmIndex, Action::Type::LOOP, 0.1f);

		vector<Vector2> backArmIndex;
		backArmIndex.push_back(Vector2(7, 2));
		backArmIndex.push_back(Vector2(10, 3));
		backArmIndex.push_back(Vector2(8, 2));
		backArmIndex.push_back(Vector2(11, 3));

		shared_ptr<Action> backArm = make_shared<Action>(backArmIndex, Action::Type::LOOP, 0.1f);

		_bodyActions.push_back(frontBody);
		_bodyActions.push_back(sideBody);
		_bodyActions.push_back(backBody);

		_armActions.push_back(frontArm);
		_armActions.push_back(sideArm);
		_armActions.push_back(backArm);
	}
#pragma endregion

#pragma region Tool
	{
		vector<Vector2> frontBody;

		frontBody.push_back(Vector2(0, 11));
		frontBody.push_back(Vector2(1, 11));
		frontBody.push_back(Vector2(2, 11));
		frontBody.push_back(Vector2(3, 11));
		frontBody.push_back(Vector2(4, 11));

		vector<Vector2> sideBody;

		sideBody.push_back(Vector2(0, 8));
		sideBody.push_back(Vector2(1, 8));
		sideBody.push_back(Vector2(2, 8));
		sideBody.push_back(Vector2(3, 8));
		sideBody.push_back(Vector2(4, 8));


		vector<Vector2> backBody;

		backBody.push_back(Vector2(0, 6));
		backBody.push_back(Vector2(1, 6));
		backBody.push_back(Vector2(2, 6));
		backBody.push_back(Vector2(3, 6));
		backBody.push_back(Vector2(4, 6));

		vector<Vector2> frontArm;

		frontArm.push_back(Vector2(6, 11));
		frontArm.push_back(Vector2(7, 11));
		frontArm.push_back(Vector2(8, 11));
		frontArm.push_back(Vector2(9, 11));
		frontArm.push_back(Vector2(10, 11));

		vector<Vector2> sideArm;

		sideArm.push_back(Vector2(6, 8));
		sideArm.push_back(Vector2(7, 8));
		sideArm.push_back(Vector2(8, 8));
		sideArm.push_back(Vector2(9, 8));
		sideArm.push_back(Vector2(10, 8));

		vector<Vector2> backArm;

		backArm.push_back(Vector2(6, 6));
		backArm.push_back(Vector2(7, 6));
		backArm.push_back(Vector2(8, 6));
		backArm.push_back(Vector2(9, 6));
		backArm.push_back(Vector2(10, 6));

		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::END);
		shared_ptr<Action> SideBody = make_shared<Action>(sideBody, Action::Type::END);
		shared_ptr<Action> BackBody = make_shared<Action>(backBody, Action::Type::END);

		_bodyActions.push_back(FrontBody);
		_bodyActions.push_back(SideBody);
		_bodyActions.push_back(BackBody);

		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END);
		shared_ptr<Action> SideArm = make_shared<Action>(sideArm, Action::Type::END);
		shared_ptr<Action> BackArm = make_shared<Action>(backArm, Action::Type::END);

		_armActions.push_back(FrontArm);
		_armActions.push_back(SideArm);
		_armActions.push_back(BackArm);
	}
#pragma endregion

#pragma region Holding
	{
		vector<Vector2> frontHolding;
		frontHolding.push_back(Vector2(12, 0));
		frontHolding.push_back(Vector2(13, 0));
		frontHolding.push_back(Vector2(14, 0));

		shared_ptr<Action> frontHAction = make_shared<Action>(frontHolding, Action::Type::LOOP, 0.1f);

		vector<Vector2> sideHolding;
		sideHolding.push_back(Vector2(12, 1));
		sideHolding.push_back(Vector2(13, 1));
		sideHolding.push_back(Vector2(14, 1));

		shared_ptr<Action> sideHAction = make_shared<Action>(sideHolding, Action::Type::LOOP, 0.1f);

		vector<Vector2> backHolding;
		backHolding.push_back(Vector2(12, 2));
		backHolding.push_back(Vector2(13, 2));
		backHolding.push_back(Vector2(14, 2));

		shared_ptr<Action> backHAction = make_shared<Action>(backHolding, Action::Type::LOOP, 0.1f);

		_armActions.push_back(frontHAction);
		_armActions.push_back(sideHAction);
		_armActions.push_back(backHAction);
	}
#pragma endregion
}

void Player::SetBodyAction(int state)
{
	state += _dir;
	if (_bodyIndex == state)
		return;

	_bodyActions[_bodyIndex]->Stop();

	_bodyIndex = state;

	_bodyActions[_bodyIndex]->Play();
}

void Player::SetArmAction(int state)
{
	state += _dir;
	if (_armIndex == state) 
		return;

	_armActions[_armIndex]->Stop();

	bool isHolding = (_playerInfo->GetState() & PlayerState::HOLDING);

	if (!isHolding) {
		_armIndex = state;
	}
	else {
		_armIndex = PlayerAction::HOLD + _dir;
	}

	_armActions[_armIndex]->Play();
}

void Player::Move()
{
	int& state = _playerInfo->GetStateRef();

	if (KEY_DOWN('W'))
	{
		if (!(state & (PlayerState::RUNL | PlayerState::RUNR)))
		{
			_dir = BACK;
			SetBodyAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);
		}
		state |= PlayerState::RUNB;
	}
	else if (KEY_PRESS('W'))
	{
		_col->AddPos(Vector2(0, 1) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('W'))
	{
		state ^= PlayerState::RUNB;

		if (state & PlayerState::RUN)
		{
			SetBodyAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);
		}
		else
		{
			SetBodyAction(PlayerAction::IDLE);
			SetArmAction(PlayerAction::IDLE);
		}
	}

	if (KEY_DOWN('S'))
	{
		if (!(state & (PlayerState::RUNL | PlayerState::RUNR)))
		{
			_dir = FRONT;
			SetBodyAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);
		}
		state |= PlayerState::RUNF;
	}
	else if (KEY_PRESS('S'))
	{
		_col->AddPos(Vector2(0, -1) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('S'))
	{
		state ^= PlayerState::RUNF;

		if (state & PlayerState::RUN)
		{
			SetBodyAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);
		}
		else
		{
			SetBodyAction(PlayerAction::IDLE);
			SetArmAction(PlayerAction::IDLE);
		}
	}

	if (!(state & PlayerState::RUNR))
	{
		if (KEY_DOWN('A'))
		{
			_dir = SIDE;
			SetBodyAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);

			state |= PlayerState::RUNL;
			_col->SetScale(Vector2(-1, 1));
		}
		else if (KEY_PRESS('A'))
		{
			state |= PlayerState::RUNL;
			SetBodyAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);

			_col->SetScale(Vector2(-1, 1));
			_col->AddPos(Vector2(-1, 0) * DELTA_TIME * SPEED);
		}
		else if (KEY_UP('A'))
		{
			state ^= PlayerState::RUNL;

			if (state & PlayerState::RUNF)
			{
				_dir = FRONT;
				SetBodyAction(PlayerAction::RUN);
				SetArmAction(PlayerAction::RUN);
			}
			else if (state & PlayerState::RUNB)
			{
				_dir = BACK;
				SetBodyAction(PlayerAction::RUN);
				SetArmAction(PlayerAction::RUN);
			}
			else
			{
				SetBodyAction(PlayerAction::IDLE);
				SetArmAction(PlayerAction::IDLE);
			}
		}
	}
	
	if (!(state & PlayerState::RUNL))
	{
		if (KEY_DOWN('D'))
		{
			_dir = SIDE;
			SetBodyAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);

			state |= PlayerState::RUNR;
			_col->SetScale(Vector2(1, 1));
		}
		if (KEY_PRESS('D'))
		{
			state |= PlayerState::RUNR;

			SetBodyAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);

			_col->SetScale(Vector2(1, 1));
			_col->AddPos(Vector2(1, 0) * DELTA_TIME * SPEED);
		}
		else if (KEY_UP('D'))
		{
			state ^= PlayerState::RUNR;

			if (state & PlayerState::RUNF)
			{
				_dir = FRONT;
				SetBodyAction(PlayerAction::RUN);
				SetArmAction(PlayerAction::RUN);
			}
			else if (state & PlayerState::RUNB)
			{
				_dir = BACK;
				SetBodyAction(PlayerAction::RUN);
				SetArmAction(PlayerAction::RUN);
			}
			else
			{
				SetBodyAction(PlayerAction::IDLE);
				SetArmAction(PlayerAction::IDLE);
			}
		}
	}
}

void Player::Items()
{
	if (KEY_DOWN('1'))
	{
		SetSelectedItemIndex(0);
	}
	else if (KEY_DOWN('2'))
	{
		SetSelectedItemIndex(1);
	}
	else if (KEY_DOWN('3'))
	{
		SetSelectedItemIndex(2);
	}
	else if (KEY_DOWN('4'))
	{
		SetSelectedItemIndex(3);
	}
	else if (KEY_DOWN('5'))
	{
		SetSelectedItemIndex(4);
	}
	else if (KEY_DOWN('6'))
	{
		SetSelectedItemIndex(5);
	}
	else if (KEY_DOWN('7'))
	{
		SetSelectedItemIndex(6);
	}
	else if (KEY_DOWN('8'))
	{
		SetSelectedItemIndex(7);
	}
	else if (KEY_DOWN('9'))
	{
		SetSelectedItemIndex(8);
	}
	else if (KEY_DOWN('0'))
	{
		SetSelectedItemIndex(9);
	}
}

void Player::Mouse()
{
	auto item = _playerInfo->GetSelectedItem();
	item->KeyInput();

	if (item->GetType() == Item::Type::NONE)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			TileMap::GetInstance()->GetFocusedTile()->Interaction();
		}
	}
}
