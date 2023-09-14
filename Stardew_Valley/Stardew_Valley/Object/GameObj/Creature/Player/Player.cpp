#include "framework.h"
#include "PlayerSubscribe.h"
#include "Player.h"

Player::Player()
	:Creature("", Vector2(20, 20))
{
	GetDatas();
	_magnatic = make_shared<CircleCollider>(50);
	_interactCol = make_shared<RectCollider>(Vector2(5,5));


	_bodySlot = make_shared<Transform>();

	_body = make_shared<LightTextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));
	_arm = make_shared<LightTextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));

	_body->SetCurFrame(Vector2(3, 0));
	_arm->SetCurFrame(Vector2(0, 0));

	_magnatic->SetParent(_col->GetTransform());
	_bodySlot->AddPos(Vector2(0, 20));
	_bodySlot->SetParent(_col->GetTransform());

	CreateAction();

	_armActions[_armIndex]->Play();
	_actions[_actionIndex]->Play();

	_isActive = true;
}

void Player::Update()
{
	Creature::Update();

	_magnatic->Update();

	_armActions[_armIndex]->Update();
		
	_arm->SetCurFrame(_armActions[_armIndex]->GetCurFrame());
}

void Player::Render()
{
	_bodySlot->Set_World(0);
	_body->Render();
	_arm->Render();


	_col->Render();
	_magnatic->Render();
}

void Player::PostRender()
{
	if (ImGui::BeginMenu("Player"))
	{
		ImGui::Text("X : %f", _col->GetWorldPos().x);
		ImGui::Text("Y : %f", _col->GetWorldPos().y);
		ImGui::EndMenu();
	}
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