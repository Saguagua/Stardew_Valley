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
}

void Player::SetSelectedItemIndex(int index)
{
	_playerInfo.lock()->SetSelectedIndex(index);
	auto items = _playerInfo.lock()->GetItems();
	int type = _playerInfo.lock()->GetItem(index)->GetType();
	int playerState = _playerInfo.lock()->GetState();

	if (type == ObjectInfo::Type::NONE ||
		type == ObjectInfo::Type::EATABLE ||
		type == ObjectInfo::Type::FARMMING ||
		type == ObjectInfo::Type::SEED)
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

	vector<Vector2> frontRunIndex;
	frontRunIndex.push_back(Vector2(1, 0));
	frontRunIndex.push_back(Vector2(0, 3));
	frontRunIndex.push_back(Vector2(2, 0));
	frontRunIndex.push_back(Vector2(1, 3));

	shared_ptr<Action> frontRunBody = make_shared<Action>(frontRunIndex, Action::Type::LOOP, 0.1f);

	vector<Vector2> sideRunIndex;
	sideRunIndex.push_back(Vector2(2, 3));
	sideRunIndex.push_back(Vector2(5, 1));
	sideRunIndex.push_back(Vector2(3, 3));
	sideRunIndex.push_back(Vector2(5, 2));

	shared_ptr<Action> sideRunBody = make_shared<Action>(sideRunIndex, Action::Type::LOOP, 0.1f);

	vector<Vector2> backRunIndex;
	backRunIndex.push_back(Vector2(4, 3));
	backRunIndex.push_back(Vector2(1, 2));
	backRunIndex.push_back(Vector2(5, 3));
	backRunIndex.push_back(Vector2(2, 2));

	shared_ptr<Action> backRunBody = make_shared<Action>(backRunIndex, Action::Type::LOOP, 0.1f);

	vector<Vector2> frontArmIndex;
	frontArmIndex.push_back(Vector2(7, 0));
	frontArmIndex.push_back(Vector2(6, 3));
	frontArmIndex.push_back(Vector2(8, 0));
	frontArmIndex.push_back(Vector2(7, 3));

	shared_ptr<Action> frontRunArm = make_shared<Action>(frontArmIndex, Action::Type::LOOP, 0.1f);

	vector<Vector2> sideArmIndex;
	sideArmIndex.push_back(Vector2(11, 1));
	sideArmIndex.push_back(Vector2(8, 3));
	sideArmIndex.push_back(Vector2(11, 2));
	sideArmIndex.push_back(Vector2(9, 3));

	shared_ptr<Action> sideRunArm = make_shared<Action>(sideArmIndex, Action::Type::LOOP, 0.1f);

	vector<Vector2> backArmIndex;
	backArmIndex.push_back(Vector2(7, 2));
	backArmIndex.push_back(Vector2(10, 3));
	backArmIndex.push_back(Vector2(8, 2));
	backArmIndex.push_back(Vector2(11, 3));

	shared_ptr<Action> backRunArm = make_shared<Action>(backArmIndex, Action::Type::LOOP, 0.1f);

	_bodyActions.push_back(frontRunBody);
	_bodyActions.push_back(sideRunBody);
	_bodyActions.push_back(backRunBody);

	_armActions.push_back(frontRunArm);
	_armActions.push_back(sideRunArm);
	_armActions.push_back(backRunArm);

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

void Player::SetAction(int state)
{
	_armActions[_armIndex]->Stop();
	_bodyActions[_bodyIndex]->Stop();

	int playerState = _playerInfo.lock()->GetState();

	if (!(playerState & PlayerInfo::PlayerState::HOLDING))
		_armIndex = state;
	else if (state % 3 == 0)
		_armIndex = PlayerAction::FRONTHOLD;
	else if (state % 3 == 1)
		_armIndex = PlayerAction::SIDEHOLD;
	else
		_armIndex = PlayerAction::BACKHOLD;

	_bodyIndex = state;

	_armActions[_armIndex]->Play();
	_bodyActions[_bodyIndex]->Play();
}

void Player::SetRun(int state)
{
	int playerState = _playerInfo.lock()->GetState();

	if (playerState == PlayerInfo::PlayerState::IDLE || playerState == PlayerInfo::PlayerState::HOLDING)
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
	}
		
}

void Player::Move()
{
	int& playerState = _playerInfo.lock()->GetStateRef();
	shared_ptr<CircleCollider> collider = _playerInfo.lock()->GetCollider();

	if (KEY_DOWN('W'))
	{
		SetRun(PlayerAction::BACKRUN);
		playerState |= PlayerInfo::PlayerState::RUNB;
	}
	else if (KEY_PRESS('W'))
	{
		collider->AddPos(Vector2(0, 1) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('W'))
	{
		playerState ^= PlayerInfo::PlayerState::RUNB;
		SetRun(PlayerAction::BACKIDLE);
	}

	if (KEY_DOWN('S'))
	{
		SetRun(PlayerAction::FRONTRUN);
		playerState |= PlayerInfo::PlayerState::RUNF;
	}
	else if (KEY_PRESS('S'))
	{
		collider->AddPos(Vector2(0, -1) * DELTA_TIME * SPEED);
	}
	else if (KEY_UP('S'))
	{
		playerState ^= PlayerInfo::PlayerState::RUNF;
		SetRun(PlayerAction::FRONTIDLE);
	}

	if (KEY_DOWN('A'))
	{
		SetRun(PlayerAction::SIDERUN);
		
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
		SetRun(PlayerAction::SIDEIDLE);
	}

	if (KEY_DOWN('D'))
	{
		SetRun(PlayerAction::SIDERUN);

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
		SetRun(PlayerAction::SIDEIDLE);
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

void Player::UpdateInfo()
{

}

void Player::Dead()
{
	//SetAction(PlayerInfo::PlayerState::DEAD);
}
