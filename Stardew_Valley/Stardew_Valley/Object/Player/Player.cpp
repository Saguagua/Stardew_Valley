#include "framework.h"
#include "../BasicObj/LightTextureRect.h"
#include "../../Data/PlayerInfo.h"
#include "Player.h"


Player::Player()
{
	_bodySlot = make_shared<Transform>();
	_body = make_shared<LightTextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));
	_arm = make_shared<LightTextureRect>(L"Resource/Player/farmer_base.png", Vector2(18, 21), Vector2(40, 60));

	_body->SetCurFrame(Vector2(3, 0));
	_arm->SetCurFrame(Vector2(0, 0));

	_bodySlot->AddPos(Vector2(0, 15));
	_bodySlot->SetParent(_playerInfo.lock()->GetTransform());

	CreateAction();

	_armActions[_armIndex]->Play();
	_bodyActions[_bodyIndex]->Play();
}

void Player::Update()
{
	KeyInput();
	_playerInfo.lock()->GetCollider()->Update();
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
	_playerInfo.lock()->GetCollider()->Render();
}

void Player::KeyInput()
{
	if (_playerInfo.lock()->GetState() & PlayerInfo::PlayerState::DEAD)
		return;

	Move();
	Items();
	Mouse();
}

void Player::SetSelectedItemIndex(int index)
{
	_playerInfo.lock()->SetSelectedIndex(index);
	auto items = _playerInfo.lock()->GetItems();
	int type = _playerInfo.lock()->GetItem(index)->GetType();
	int playerState = _playerInfo.lock()->GetState();

	if (type == Item::Type::NONE ||
		type == Item::Type::EATABLE ||
		type == Item::Type::FRTI ||
		type == Item::Type::SEED)
	{
		playerState |= PlayerInfo::PlayerState::HOLDING;
	}
	else
	{
		playerState &= ~(PlayerInfo::PlayerState::HOLDING);
	}

	_playerInfo.lock()->SetState(playerState);

	SetAction(_bodyIndex);
}

void Player::CreateAction()
{
	//Idle
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
	
	//Run
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
	
	//Tool
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

	//Holding
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

	

	
}

void Player::SetAction(int state)
{
	_armActions[_armIndex]->Stop();
	_bodyActions[_bodyIndex]->Stop();

	int playerState = _playerInfo.lock()->GetState();

	if (!(playerState & PlayerInfo::PlayerState::HOLDING))
		_armIndex = state + _dir;
	else
		_armIndex = PlayerAction::HOLD + _dir;

	_bodyIndex = state + _dir;

	_armActions[_armIndex]->Play();
	_bodyActions[_bodyIndex]->Play();
}

void Player::SetRun(int state)
{
	int playerState = _playerInfo.lock()->GetState();

	/*if (playerState == PlayerInfo::PlayerState::IDLE || playerState == PlayerInfo::PlayerState::HOLDING)
		SetAction(state);
	else if (playerState & (PlayerInfo::PlayerState::RUNL | PlayerInfo::PlayerState::RUNR))
		SetAction(PlayerAction::SIDERUN);
	else 
	{
		if (state == PlayerInfo::PlayerState::RUNL || state == PlayerInfo::PlayerState::RUNR)
			SetAction(PlayerAction::SIDERUN);
		else if(playerState & PlayerInfo::PlayerState::RUNF)
			SetAction(PlayerAction::FRONTRUN);
		else if (playerState & PlayerInfo::PlayerState::RUNB)
			SetAction(PlayerAction::BACKRUN);
	}*/
		
}

void Player::Move()
{
	int& playerState = _playerInfo.lock()->GetStateRef();
	shared_ptr<CircleCollider> collider = _playerInfo.lock()->GetCollider();

	if (KEY_DOWN('W'))
	{
		SetRun(PlayerAction::RUN);
		_dir = Direction::BACK;
		playerState |= PlayerInfo::PlayerState::RUNB;
	}
	else if (KEY_PRESS('W'))
	{
		collider->AddPos(Vector2(0, 1) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('W'))
	{
		playerState ^= PlayerInfo::PlayerState::RUNB;
		SetRun(PlayerAction::IDLE);
	}

	if (KEY_DOWN('S'))
	{
		_dir = Direction::FRONT;
		SetRun(PlayerAction::RUN);
		playerState |= PlayerInfo::PlayerState::RUNF;
	}
	else if (KEY_PRESS('S'))
	{
		collider->AddPos(Vector2(0, -1) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('S'))
	{
		playerState ^= PlayerInfo::PlayerState::RUNF;
		SetRun(PlayerAction::IDLE);
	}

	if (KEY_DOWN('A'))
	{
		_dir = Direction::SIDE;
		SetRun(PlayerAction::RUN);
		
		playerState |= PlayerInfo::PlayerState::RUNL;
		collider->SetScale(Vector2(-1, 1));
	}
	else if (KEY_PRESS('A'))
	{
		collider->AddPos(Vector2(-1, 0) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('A'))
	{
		playerState ^= PlayerInfo::PlayerState::RUNL;
		SetRun(PlayerAction::IDLE);
	}

	if (KEY_DOWN('D'))
	{
		_dir = Direction::SIDE;
		SetRun(PlayerAction::RUN);

		playerState |= PlayerInfo::PlayerState::RUNR;
		collider->SetScale(Vector2(1, 1));
	}
	if (KEY_PRESS('D'))
	{
		collider->AddPos(Vector2(1, 0) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('D'))
	{
		playerState ^= PlayerInfo::PlayerState::RUNR;
		SetRun(PlayerAction::IDLE);
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
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 target = W_MOUSE_POS - _playerInfo.lock()->GetWorldPos();
		float angle = target.Angle() * 57.2958f;

		if (angle > -35.0f && angle <= 35.0f)
		{
			_dir = Direction::SIDE;
			_playerInfo.lock()->SetScale(Vector2(1, 1));
		}
		else if (angle > 35.0f && angle <= 105.0f)
		{
			_dir = Direction::BACK;
		}
		else if (angle > -105.0f && angle <= -35.0f)
		{
			_dir = Direction::FRONT;
			
		}
		else
		{
			_dir = Direction::SIDE;
			_playerInfo.lock()->SetScale(Vector2(-1, 1));
		}
	}
	else if (KEY_UP(VK_LBUTTON))
	{
		auto item = DATA->GetSelectedItem();

		if (item->GetType() == Item::Type::PICKAXE ||
			item->GetType() == Item::Type::AXE ||
			item->GetType() == Item::Type::HOE)
		{
			SetAction(PlayerAction::TOOL);
		}
	}
	
}

void Player::UpdateInfo()
{
}

void Player::Dead()
{
	//SetAction(PlayerInfo::PlayerState::DEAD);
}
