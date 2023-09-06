#include "framework.h"
#include "PlayerSubscribe.h"
#include "Player.h"

Player::Player()
	:Creature("", Vector2(20, 20))
{
	GetDatas();
	_magnatic = make_shared<CircleCollider>(50);
	_col->SetDebug(true);
	_magnatic->SetDebug(true);

	_bodySlot = make_shared<Transform>();
	_itemSlot = make_shared<Transform>();

	_body = make_shared<LightTextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));
	_arm = make_shared<LightTextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));
	_obj = make_shared<Sprite>(XMLPATH1, "BLANK", Vector2(30, 30), SpriteType::OBJECT);

	_body->SetCurFrame(Vector2(3, 0));
	_arm->SetCurFrame(Vector2(0, 0));

	_magnatic->SetParent(_col->GetTransform());
	_bodySlot->AddPos(Vector2(0, 20));
	_bodySlot->SetParent(_col->GetTransform());
	_itemSlot->AddPos(Vector2(0, 30));
	_itemSlot->SetParent(_bodySlot);
	CreateAction();

	_armActions[_armIndex]->Play();
	_actions[_actionIndex]->Play();

	_isActive = true;
}

void Player::Update()
{
	Creature::Update();

	_magnatic->Update();
	_itemSlot->Update();

	_armActions[_armIndex]->Update();
		
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

vector<CallBackInt> Player::GetCurIndexCallback()
{
	vector<CallBackInt> v;

	/*for (int i = 0; i < 10; i++)
	{
		CallBackInt cb = std::bind(&Player::SetSelectedItemIndex, this, i);
	}*/

	return v;
}

void Player::GetDatas()
{
	auto info	= DATA->GetPlayerInfo();
	_maxHp		= info->GetMaxHP();
	_hp			= info->GetHP();
	_maxStamina = info->GetMaxStamina();
	_stamina	= info->GetStamina();
	_items		= info->GetItems();
	_state		= info->GetState();
	
	_col->SetPos(info->GetPos());
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

		_actions.push_back(frontIdleB);
		_actions.push_back(sideIdleB);
		_actions.push_back(backIdleB);

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

		_actions.push_back(frontBody);
		_actions.push_back(sideBody);
		_actions.push_back(backBody);

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


		CallBack cb = std::bind(&Player::SetIdle, this);

		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::END);
		shared_ptr<Action> SideBody = make_shared<Action>(sideBody, Action::Type::END);
		shared_ptr<Action> BackBody = make_shared<Action>(backBody, Action::Type::END);

		FrontBody->SetEndEvent(cb);
		SideBody->SetEndEvent(cb);
		BackBody->SetEndEvent(cb);

		_actions.push_back(FrontBody);
		_actions.push_back(SideBody);
		_actions.push_back(BackBody);

		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END);
		shared_ptr<Action> SideArm = make_shared<Action>(sideArm, Action::Type::END);
		shared_ptr<Action> BackArm = make_shared<Action>(backArm, Action::Type::END);

		FrontArm->SetEndEvent(cb);
		SideArm->SetEndEvent(cb);
		BackArm->SetEndEvent(cb);

		_armActions.push_back(FrontArm);
		_armActions.push_back(SideArm);
		_armActions.push_back(BackArm);
	}
#pragma endregion

#pragma region Tool2
	{
		CallBack cb = std::bind(&Player::SetIdle, this);

		vector<Vector2> frontBody;

		frontBody.push_back(Vector2(0, 9));
		frontBody.push_back(Vector2(1, 9));

		vector<Vector2> frontArm;

		frontArm.push_back(Vector2(6, 9));
		frontArm.push_back(Vector2(7 ,9));

		vector<Vector2> sideBody;

		sideBody.push_back(Vector2(4, 9));
		sideBody.push_back(Vector2(5, 9));

		vector<Vector2> sideArm;

		sideArm.push_back(Vector2(10, 9));
		sideArm.push_back(Vector2(11, 9));

		vector<Vector2> backBody;

		backBody.push_back(Vector2(2, 10));
		backBody.push_back(Vector2(3, 10));

		vector<Vector2> backArm;

		backArm.push_back(Vector2(8, 10));
		backArm.push_back(Vector2(9, 10));

		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::END, 0.2f);
		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END, 0.2f);
		shared_ptr<Action> SideBody = make_shared<Action>(sideBody, Action::Type::END, 0.2f);
		shared_ptr<Action> SideArm = make_shared<Action>(sideArm, Action::Type::END, 0.2f);
		shared_ptr<Action> BackBody = make_shared<Action>(backBody, Action::Type::END, 0.2f);
		shared_ptr<Action> BackArm = make_shared<Action>(backArm, Action::Type::END, 0.2f);
		
		FrontBody->SetEndEvent(cb);
		SideBody->SetEndEvent(cb);
		BackBody->SetEndEvent(cb);

		_actions.push_back(FrontBody);
		_actions.push_back(SideBody);
		_actions.push_back(BackBody);

		_armActions.push_back(FrontArm);
		_armActions.push_back(SideArm);
		_armActions.push_back(BackArm);

	}
#pragma endregion

#pragma region FishingStart
	{
		vector<Vector2> frontBody;

		frontBody.push_back(Vector2(0, 11));
		frontBody.push_back(Vector2(1, 11));
		frontBody.push_back(Vector2(2, 11));
		frontBody.push_back(Vector2(3, 11));
		frontBody.push_back(Vector2(4, 11));
		frontBody.push_back(Vector2(1, 11));

		vector<Vector2> sideBody;

		sideBody.push_back(Vector2(0, 8));
		sideBody.push_back(Vector2(1, 8));
		sideBody.push_back(Vector2(2, 8));
		sideBody.push_back(Vector2(3, 8));
		sideBody.push_back(Vector2(4, 8));
		sideBody.push_back(Vector2(1, 10));


		vector<Vector2> backBody;

		backBody.push_back(Vector2(0, 6));
		backBody.push_back(Vector2(1, 6));
		backBody.push_back(Vector2(2, 6));
		backBody.push_back(Vector2(3, 6));
		backBody.push_back(Vector2(4, 6));
		backBody.push_back(Vector2(5, 13));

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

		CallBack cb = std::bind(&FishingSystem::ActiveFishingHook, FishingSystem::GetInstance());
		
		FrontBody->SetEndEvent(cb);
		SideBody->SetEndEvent(cb);
		BackBody->SetEndEvent(cb);

		_actions.push_back(FrontBody);
		_actions.push_back(SideBody);
		_actions.push_back(BackBody);

		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END);
		shared_ptr<Action> SideArm = make_shared<Action>(sideArm, Action::Type::END);
		shared_ptr<Action> BackArm = make_shared<Action>(backArm, Action::Type::END);

		_armActions.push_back(FrontArm);
		_armActions.push_back(SideArm);
		_armActions.push_back(BackArm);
	}
#pragma endregion

#pragma region FishingGame
	{
		vector<Vector2> frontBody;

		frontBody.push_back(Vector2(2, 12));
		frontBody.push_back(Vector2(3, 12));

		vector<Vector2> frontArm;
		
		frontArm.push_back(Vector2(8, 12));
		frontArm.push_back(Vector2(9, 12));

		vector<Vector2> sideBody;

		sideBody.push_back(Vector2(0, 12));
		sideBody.push_back(Vector2(1, 12));

		vector<Vector2> sideArm;

		sideArm.push_back(Vector2(6, 12));
		sideArm.push_back(Vector2(7, 12));

		vector<Vector2> backBody;

		backBody.push_back(Vector2(4, 12));
		backBody.push_back(Vector2(5, 12));

		vector<Vector2> backArm;

		backArm.push_back(Vector2(10, 12));
		backArm.push_back(Vector2(11, 12));

		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::LOOP, 0.5f);
		shared_ptr<Action> SideBody = make_shared<Action>(sideBody, Action::Type::LOOP, 0.5f);
		shared_ptr<Action> BackBody = make_shared<Action>(backBody, Action::Type::LOOP, 0.5f);
		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::LOOP, 0.5f);
		shared_ptr<Action> SideArm = make_shared<Action>(sideArm, Action::Type::LOOP, 0.5f);
		shared_ptr<Action> BackArm = make_shared<Action>(backArm, Action::Type::LOOP, 0.5f);

		_actions.push_back(FrontBody);
		_actions.push_back(SideBody);
		_actions.push_back(BackBody);

		_armActions.push_back(FrontArm);
		_armActions.push_back(SideArm);
		_armActions.push_back(BackArm);
	}
#pragma endregion

#pragma region FishingEnd
	{
		vector<Vector2> frontBody;

		frontBody.push_back(Vector2(0, 9));
		frontBody.push_back(Vector2(1, 9));
		frontBody.push_back(Vector2(2, 9));
		frontBody.push_back(Vector2(3, 9));

		vector<Vector2> frontArm;

		frontArm.push_back(Vector2(6, 9));
		frontArm.push_back(Vector2(7, 9));
		frontArm.push_back(Vector2(8, 9));
		frontArm.push_back(Vector2(9, 9));

		vector<Vector2> sideBody;

		sideBody.push_back(Vector2(4, 9));
		sideBody.push_back(Vector2(5, 9));
		sideBody.push_back(Vector2(0, 10));
		sideBody.push_back(Vector2(1, 10));

		vector<Vector2> sideArm;

		sideArm.push_back(Vector2(10, 9));
		sideArm.push_back(Vector2(11, 9));
		sideArm.push_back(Vector2(6, 10));
		sideArm.push_back(Vector2(7, 10));

		vector<Vector2> backBody;

		backBody.push_back(Vector2(2, 10));
		backBody.push_back(Vector2(3, 10));
		backBody.push_back(Vector2(4, 10));
		backBody.push_back(Vector2(5, 10));

		vector<Vector2> backArm;

		backArm.push_back(Vector2(8, 10));
		backArm.push_back(Vector2(9, 10));
		backArm.push_back(Vector2(10, 10));
		backArm.push_back(Vector2(11, 10));

		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::END, 0.15f);
		shared_ptr<Action> SideBody = make_shared<Action>(sideBody, Action::Type::END, 0.15f);
		shared_ptr<Action> BackBody = make_shared<Action>(backBody, Action::Type::END, 0.15f);
		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END, 0.15f);
		shared_ptr<Action> SideArm = make_shared<Action>(sideArm, Action::Type::END, 0.15f);
		shared_ptr<Action> BackArm = make_shared<Action>(backArm, Action::Type::END, 0.15f);

		CallBack cb = std::bind(&Player::SetIdle, this);

		FrontBody->SetEndEvent(cb);
		SideBody->SetEndEvent(cb);
		BackBody->SetEndEvent(cb);

		_actions.push_back(FrontBody);
		_actions.push_back(SideBody);
		_actions.push_back(BackBody);

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

void Player::SetArmAction(int state)
{
	state += _direction;
	if (_armIndex == state) 
		return;

	_armActions[_armIndex]->Reset();

	bool isHolding = (_state & PlayerState::HOLDING);

	if (!isHolding) {
		_armIndex = state;
	}
	else {
		_armIndex = PlayerAction::HOLD + _direction;
	}

	_armActions[_armIndex]->Play();
}

void Player::SetIdle()
{
	SetAction(PlayerAction::IDLE);
	SetArmAction(PlayerAction::IDLE);
	_freeze = false;
}

void Player::SetNextAction(int index)
{
	SetAction(index);
	SetArmAction(index);
}

void Player::Move()
{
	if (KEY_DOWN('W'))
	{
		if (!(_state & (PlayerState::RUNL | PlayerState::RUNR)))
		{
			_direction = BACK;
			SetAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);
		}
		_state |= PlayerState::RUNB;
	}
	else if (KEY_PRESS('W'))
	{
		_col->AddPos(Vector2(0, 1) * DELTA_TIME * 200);
	}
	else if (KEY_UP('W'))
	{
		_state ^= PlayerState::RUNB;

		if (_state & PlayerState::RUN)
		{
			SetAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);
		}
		else
		{
			SetAction(PlayerAction::IDLE);
			SetArmAction(PlayerAction::IDLE);
		}
	}

	if (KEY_DOWN('S'))
	{
		if (!(_state & (PlayerState::RUNL | PlayerState::RUNR)))
		{
			_direction = FRONT;
			SetAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);
		}
		_state |= PlayerState::RUNF;
	}
	else if (KEY_PRESS('S'))
	{
		_col->AddPos(Vector2(0, -1) * DELTA_TIME * 200);
	}
	else if (KEY_UP('S'))
	{
		_state ^= PlayerState::RUNF;

		if (_state & PlayerState::RUN)
		{
			SetAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);
		}
		else
		{
			SetAction(PlayerAction::IDLE);
			SetArmAction(PlayerAction::IDLE);
		}
	}

	if (!(_state & PlayerState::RUNR))
	{
		if (KEY_DOWN('A'))
		{
			_direction = SIDE;
			SetAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);

			_state |= PlayerState::RUNL;
			_col->SetScale(Vector2(-1, 1));
		}
		else if (KEY_PRESS('A'))
		{
			_state |= PlayerState::RUNL;
			SetAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);

			_col->SetScale(Vector2(-1, 1));
			_col->AddPos(Vector2(-1, 0) * DELTA_TIME * 200);
		}
		else if (KEY_UP('A'))
		{
			_state ^= PlayerState::RUNL;

			if (_state & PlayerState::RUNF)
			{
				_direction = FRONT;
				SetAction(PlayerAction::RUN);
				SetArmAction(PlayerAction::RUN);
			}
			else if (_state & PlayerState::RUNB)
			{
				_direction = BACK;
				SetAction(PlayerAction::RUN);
				SetArmAction(PlayerAction::RUN);
			}
			else
			{
				SetAction(PlayerAction::IDLE);
				SetArmAction(PlayerAction::IDLE);
			}
		}
	}
	
	if (!(_state & PlayerState::RUNL))
	{
		if (KEY_DOWN('D'))
		{
			_direction = SIDE;
			SetAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);

			_state |= PlayerState::RUNR;
			_col->SetScale(Vector2(1, 1));
		}
		if (KEY_PRESS('D'))
		{
			_state |= PlayerState::RUNR;

			SetAction(PlayerAction::RUN);
			SetArmAction(PlayerAction::RUN);

			_col->SetScale(Vector2(1, 1));
			_col->AddPos(Vector2(1, 0) * DELTA_TIME * 200);
		}
		else if (KEY_UP('D'))
		{
			_state ^= PlayerState::RUNR;

			if (_state & PlayerState::RUNF)
			{
				_direction = FRONT;
				SetAction(PlayerAction::RUN);
				SetArmAction(PlayerAction::RUN);
			}
			else if (_state & PlayerState::RUNB)
			{
				_direction = BACK;
				SetAction(PlayerAction::RUN);
				SetArmAction(PlayerAction::RUN);
			}
			else
			{
				SetAction(PlayerAction::IDLE);
				SetArmAction(PlayerAction::IDLE);
			}
		}
	}
}