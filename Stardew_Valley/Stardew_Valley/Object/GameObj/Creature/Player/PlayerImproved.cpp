#include "framework.h"
#include "PlayerSubscribe.h"
#include "PlayerImproved.h"

PlayerImproved::PlayerImproved()
	:Player()
{
	_handSlot = make_shared<Transform>();
	_itemSlot = make_shared<Transform>();
	_itemRenderer = make_shared<Sprite>("BLANK", Vector2(30, 30), SpriteType::OBJECT);

	_handSlot->AddPos(Vector2(0, 30));
	_handSlot->SetParent(_bodySlot);

	_itemSlot->AddPos(Vector2(0, 5));
	_itemSlot->SetParent(_handSlot);
	CreateAction();
}

void PlayerImproved::Initialize()
{
	for (auto item : _items)
		item->SetPlayer(shared_from_this());
}

void PlayerImproved::Update()
{
	Player::Update();
	_handSlot->Update();
	_itemSlot->Update();

	if (_toolActive)
	{
		if (!_toolActions[_itemActionIndex]->IsPlay())
			return;

		_toolActions[_itemActionIndex]->Update();
		_itemRenderer->SetIndex(_toolActions[_itemActionIndex]->GetCurFrame().x);
		
		UpdateHandSlot();
	}
}

void PlayerImproved::Render()
{
	if (_direction == BACK)
	{
		if (_toolActive)
		{
			_itemSlot->Set_World(0);

			_itemRenderer->Render();
		}
		_bodySlot->Set_World(0);
		_body->Render();
		_arm->Render();
	}
	else
	{
		_bodySlot->Set_World(0);
		_body->Render();
		_arm->Render();


		if (_toolActive)
		{
			_itemSlot->Set_World(0);

			_itemRenderer->Render();
		}
	}
	
	_col->Render();
	_magnatic->Render();
}

void PlayerImproved::PlayAction(int action)
{
	SetAction(action);
	SetArmAction(action);
}

void PlayerImproved::RequestSubscribe(PlayerSubscribe* subscriber)
{
    _subscribers.push_back(subscriber);
}

void PlayerImproved::CancelSubscribe(PlayerSubscribe* subscriber)
{
	for (auto subscriber : _subscribers)
	{
		if (subscriber == subscriber)
			_subscribers.remove(subscriber);
	}
}

void PlayerImproved::KeyInput()
{
	ItemAction();
	
	if (!_freeze)
	{
		Player::Move();
		ChangeIndex();
	}
}

void PlayerImproved::SetMap(shared_ptr<TileMap> map)
{
	_map = map;
	for (auto item : _items)
		item->SetMap(map);
}

bool PlayerImproved::AddItem(string name)
{
	int empty = -1;

	for (int i = 0; i < _items.size(); i++)
	{
		if (_items[i]->GetName() == name)
		{
			if (_items[i]->AddCount())
			{
				SendToSubscribers(PlayerSubscribe::Type::ITEMS);
				return true;
			}
		}
		else if (empty == -1 && _items[i]->GetName() == "BLANK")
		{
			empty = i;
		}
	}
	if (empty != -1)
	{
		_items[empty]->SetItem(name, 1);
		SendToSubscribers(PlayerSubscribe::Type::ITEMS);
		return true;
	}

	return false;
}

void PlayerImproved::SendToSubscribers(int type)
{
	for (auto subscriber : _subscribers)
	{
		if (subscriber->_type == type)
			subscriber->UpdateInfo();
	}
}

void PlayerImproved::SetCurItem(int index)
{
	_curIndex = index;
	int type = _items[_curIndex]->GetType();
	int armIndex = _armIndex;

	if (type == Item::Type::NONE ||
		type == Item::Type::EATABLE ||
		type == Item::Type::FERTILIZER ||
		type == Item::Type::SEED)
	{
		_state |= PlayerState::HOLDING;
		_itemRenderer->SetImage(_items[_curIndex]->GetName(), _items[_curIndex]->GetIndex());
		armIndex = PlayerAction::HOLD;
	}
	else
	{
		_state &= ~(PlayerState::HOLDING);
		_itemRenderer->SetImage("BLANK");
		if (_state != PlayerState::RUN)
			armIndex = PlayerAction::IDLE;
		else
			armIndex = PlayerAction::RUN;
	}

	SetArmAction(armIndex);
}

void PlayerImproved::ChangeIndex()
{
	if (KEY_DOWN('1'))
	{
		SetCurItem(0);
	}
	else if (KEY_DOWN('2'))
	{
		SetCurItem(1);
	}
	else if (KEY_DOWN('3'))
	{
		SetCurItem(2);
	}
	else if (KEY_DOWN('4'))
	{
		SetCurItem(3);
	}
	else if (KEY_DOWN('5'))
	{
		SetCurItem(4);
	}
	else if (KEY_DOWN('6'))
	{
		SetCurItem(5);
	}
	else if (KEY_DOWN('7'))
	{
		SetCurItem(6);
	}
	else if (KEY_DOWN('8'))
	{
		SetCurItem(7);
	}
	else if (KEY_DOWN('9'))
	{
		SetCurItem(8);
	}
	else if (KEY_DOWN('0'))
	{
		SetCurItem(9);
	}
}

void PlayerImproved::ItemAction()
{
	int type = _items[_curIndex]->GetType();

	switch (type)
	{
	case Item::Type::AXE:
	case Item::Type::PICKAXE:
	case Item::Type::HOE:
	{
		if (KEY_DOWN(VK_LBUTTON) && !_freeze)
		{
			string name = _items[_curIndex]->GetName();

			SetDirection(W_MOUSE_POS);

			if (_direction == FRONT)
			{
				name += "F";
				_itemActionIndex = 0;
				_handSlot->SetPos(Vector2(-10, 0));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 50, -50 };
				_handSlotRotate = 0.0f;
			}
			else if (_direction == SIDE)
			{
				name += "S";
				_itemActionIndex = 1;
				_handSlot->SetPos(Vector2(-10, 10));
				_handSlot->SetAngle(0.7f);
				_handSlotDirection = { 80, -25 };
				_handSlotRotate = -6.5f;
			}
			else
			{
				name += "B";
				_itemActionIndex = 0;
				_handSlot->SetPos(Vector2(0, 10));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 0, 50 };
				_handSlotRotate = 0.0f;
			}

			_itemRenderer->SetImage(name);

			_handSlot->SetScale(DATA->GetXMLInfo(name)->GetSize(0));

			SetAction(PlayerAction::TOOL);
			SetArmAction(PlayerAction::TOOL);
			_toolActions[_itemActionIndex]->Play();

			_toolActive = true;
			_freeze = true;
			SetPause(true);

			_items[_curIndex]->StartCharging(0, 1, _items[_curIndex]->GetVals()[0], 1);
		}
		else if (KEY_PRESS(VK_LBUTTON))
		{
			_items[_curIndex]->Charging();
		}
		else if (KEY_UP(VK_LBUTTON))
		{
			SetPause(false);
		}
		break;
	}
	case Item::Type::WATERINGCAN:
	{
		if (KEY_DOWN(VK_LBUTTON) && !_freeze)
		{
			string name = _items[_curIndex]->GetName();

			SetDirection(W_MOUSE_POS);

			if (_direction == FRONT)
			{
				name += "F";
				_itemActionIndex = 2;
				_handSlot->SetPos(Vector2(0, -20));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 0, 35 };
				_handSlotRotate = 0.0f;
			}
			else if (_direction == SIDE)
			{
				name += "S";
				_itemActionIndex = 3;
				_handSlot->SetPos(Vector2(20, -10));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 0, 20 };
				_handSlotRotate = 0.0f;
			}
			else
			{
				name += "B";
				_itemActionIndex = 4;
				_handSlot->SetPos(Vector2(0, 0));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 0, 35 };
				_handSlotRotate = 0.0f;
			}

			_itemRenderer->SetImage(name);

			_handSlot->SetScale(DATA->GetXMLInfo(name)->GetSize(0));

			SetAction(PlayerAction::TOOL2);
			SetArmAction(PlayerAction::TOOL2);
			_toolActions[_itemActionIndex]->Play();

			_toolActive = true;
			_freeze = true;
			SetPause(true);

			_items[_curIndex]->StartCharging(0, 1, _items[_curIndex]->GetVals()[0], 1);
		}
		else if (KEY_PRESS(VK_LBUTTON))
		{
			_items[_curIndex]->Charging();
		}
		else if (KEY_UP(VK_LBUTTON))
		{
			SetPause(false);
		}
	
		break;
	}
	case Item::Type::EATABLE:
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			_items[_curIndex]->Use();
		}
	}
	case Item::FISHINGROD:
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			string name = _items[_curIndex]->GetName();

			SetDirection(W_MOUSE_POS);

			if (_direction == FRONT)
			{
				name += "F";
				_itemActionIndex = 0;
				_handSlot->SetPos(Vector2(-10, 0));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 50, -50 };
				_handSlotRotate = 0.0f;
			}
			else if (_direction == SIDE)
			{
				name += "S";
				_itemActionIndex = 1;
				_handSlot->SetPos(Vector2(-10, 10));
				_handSlot->SetAngle(0.7f);
				_handSlotDirection = { 80, -25 };
				_handSlotRotate = -6.5f;
			}
			else
			{
				name += "F";
				_itemActionIndex = 0;
				_handSlot->SetPos(Vector2(0, 10));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 0, 50 };
				_handSlotRotate = 0.0f;
			}

			_itemRenderer->SetImage(name);

			_handSlot->SetScale(DATA->GetXMLInfo(name)->GetSize(0));

			SetAction(PlayerAction::FISHING1);
			SetArmAction(PlayerAction::FISHING1);
			_toolActions[_itemActionIndex]->Play();

			_toolActive = true;
			_freeze = true;
			SetPause(true);

			_items[_curIndex]->StartCharging(0, 1, _items[_curIndex]->GetVals()[0], 1);
		}
		else if (KEY_UP(VK_LBUTTON))
		{
			SetPause(false);
		}
	}
	case Item::Type::WEAPON:
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			SetDirection(W_MOUSE_POS);
			SetAction(PlayerAction::ATTACK);
			SetArmAction(PlayerAction::ATTACK);
			SetFreeze(true);
		}
	}
	case Item::Type::SEED:
	case Item::Type::FACILITY:
	{
		if (KEY_DOWN(VK_LBUTTON))
			_items[_curIndex]->Use();
		break;
	}

	default:
		break;
	}
}

void PlayerImproved::SetPause(bool val)
{
	_actions[_actionIndex]->Pause(val);
	_armActions[_armIndex]->Pause(val);
	_toolActions[_itemActionIndex]->Pause(val);
}

void PlayerImproved::UpdateHandSlot()
{
	_handSlot->AddPos(_handSlotDirection * DELTA_TIME);
	_handSlot->AddAngle(_handSlotRotate * DELTA_TIME);
}

void PlayerImproved::SwapItems(int index1, int index2)
{
	shared_ptr<Item> tmp = _items[index1];
	_items[index1] = _items[index2];
	_items[index2] = tmp;

	SendToSubscribers(PlayerSubscribe::Type::ITEMS);
}

void PlayerImproved::ToolEndEvent()
{
	_items[_curIndex]->Use();
	_toolActive = false;
	_freeze = false;
}

void PlayerImproved::AddMaxHP(short cost)
{
}

void PlayerImproved::AddMaxStamina(short cost)
{
}

void PlayerImproved::AddHP(short cost)
{
	_hp += cost;

	if (_hp <= 0)
		_state = (PlayerState::DEAD);

	float ratio = (float)_hp / (float)_maxHp;
	PlayerUI::GetInstance()->SetHP(ratio);
}

void PlayerImproved::AddStamina(short cost)
{
	_stamina += cost;

	if (_stamina <= 0)
		_state = (PlayerState::DEAD);

	float ratio = (float)_stamina / (float)_maxStamina;
	PlayerUI::GetInstance()->SetStamina(ratio);
}


void PlayerImproved::CreateAction()
{

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


		CallBack cb = std::bind(&PlayerImproved::SetIdle, this);


		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::END, 0.07f);
		shared_ptr<Action> SideBody = make_shared<Action>(sideBody, Action::Type::END, 0.07f);
		shared_ptr<Action> BackBody = make_shared<Action>(backBody, Action::Type::END, 0.07f);

		FrontBody->AddEndEvent(cb);
		SideBody->AddEndEvent(cb);
		BackBody->AddEndEvent(cb);

		_actions.push_back(FrontBody);
		_actions.push_back(SideBody);
		_actions.push_back(BackBody);

		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END, 0.07f);
		shared_ptr<Action> SideArm = make_shared<Action>(sideArm, Action::Type::END, 0.07f);
		shared_ptr<Action> BackArm = make_shared<Action>(backArm, Action::Type::END, 0.07f);

		FrontArm->AddEndEvent(cb);
		SideArm->AddEndEvent(cb);
		BackArm->AddEndEvent(cb);

		_armActions.push_back(FrontArm);
		_armActions.push_back(SideArm);
		_armActions.push_back(BackArm);
	}
#pragma endregion

#pragma region Tool2
	{
		CallBack cb = std::bind(&PlayerImproved::SetIdle, this);

		vector<Vector2> frontBody;

		frontBody.push_back(Vector2(0, 9));
		frontBody.push_back(Vector2(1, 9));

		vector<Vector2> frontArm;

		frontArm.push_back(Vector2(6, 9));
		frontArm.push_back(Vector2(7, 9));

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

		FrontBody->AddEndEvent(cb);
		SideBody->AddEndEvent(cb);
		BackBody->AddEndEvent(cb);

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

		FrontBody->AddEndEvent(cb);
		SideBody->AddEndEvent(cb);
		BackBody->AddEndEvent(cb);

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

		CallBack cb = std::bind(&PlayerImproved::SetIdle, this);

		FrontBody->AddEndEvent(cb);
		SideBody->AddEndEvent(cb);
		BackBody->AddEndEvent(cb);

		_actions.push_back(FrontBody);
		_actions.push_back(SideBody);
		_actions.push_back(BackBody);

		_armActions.push_back(FrontArm);
		_armActions.push_back(SideArm);
		_armActions.push_back(BackArm);
	}
#pragma endregion

#pragma region ToolActionsPick,Axe,Hoe
	{
		vector<Vector2> toolFront;
		toolFront.push_back(Vector2(0, 0));
		toolFront.push_back(Vector2(1, 0));

		shared_ptr<Action> ToolFront = make_shared<Action>(toolFront, Action::Type::END, 0.1f);

		vector<Vector2> toolSide;
		toolSide.push_back(Vector2(0, 0));
		shared_ptr<Action> ToolSide = make_shared<Action>(toolSide, Action::Type::END, 0.2f);

		vector<Vector2> toolBack;
		toolBack.push_back(Vector2(0, 0));
		toolBack.push_back(Vector2(1, 0));
		shared_ptr<Action>ToolBack = make_shared<Action>(toolBack, Action::Type::END, 0.1f);

		CallBack endEvent = std::bind(&PlayerImproved::ToolEndEvent, this);

		ToolFront->AddEndEvent(endEvent);
		ToolSide->AddEndEvent(endEvent);
		ToolBack->AddEndEvent(endEvent);

		_toolActions.push_back(ToolFront);
		_toolActions.push_back(ToolSide);
		_toolActions.push_back(ToolBack);
	}
#pragma endregion

#pragma region ToolActionWatering
	{
		vector<Vector2> toolFront;
		toolFront.push_back(Vector2(0, 0));
		toolFront.push_back(Vector2(1, 0));

		shared_ptr<Action> ToolFront = make_shared<Action>(toolFront, Action::Type::END, 0.1f);

		vector<Vector2> toolSide;
		toolSide.push_back(Vector2(0, 0));
		shared_ptr<Action> ToolSide = make_shared<Action>(toolSide, Action::Type::END, 0.4f);

		vector<Vector2> toolBack;
		toolBack.push_back(Vector2(0, 0));
		shared_ptr<Action>ToolBack = make_shared<Action>(toolBack, Action::Type::END, 0.1f);

		CallBack endEvent = std::bind(&PlayerImproved::ToolEndEvent, this);

		ToolFront->AddEndEvent(endEvent);
		ToolSide->AddEndEvent(endEvent);
		ToolBack->AddEndEvent(endEvent);

		_toolActions.push_back(ToolFront);
		_toolActions.push_back(ToolSide);
		_toolActions.push_back(ToolBack);
	}
#pragma endregion


#pragma region ToolActionFishingStart
	{
		vector<Vector2> toolFront;
		toolFront.push_back(Vector2(0, 0));
		toolFront.push_back(Vector2(1, 0));
		toolFront.push_back(Vector2(2, 0));

		shared_ptr<Action> ToolFront = make_shared<Action>(toolFront, Action::Type::END, 0.1f);

		vector<Vector2> toolSide;
		toolSide.push_back(Vector2(0, 0));
		toolSide.push_back(Vector2(1, 0));
		toolSide.push_back(Vector2(2, 0));
		toolSide.push_back(Vector2(3, 0));
		toolSide.push_back(Vector2(4, 0));
		toolSide.push_back(Vector2(5, 0));
		shared_ptr<Action> ToolSide = make_shared<Action>(toolSide, Action::Type::END, 0.4f);

		vector<Vector2> toolBack;
		toolBack.push_back(Vector2(0, 0));
		toolBack.push_back(Vector2(1, 0));
		toolBack.push_back(Vector2(2, 0));
		shared_ptr<Action>ToolBack = make_shared<Action>(toolBack, Action::Type::END, 0.1f);

		CallBack endEvent = std::bind(&PlayerImproved::ToolEndEvent, this);

		ToolFront->AddEndEvent(endEvent);
		ToolSide->AddEndEvent(endEvent);
		ToolBack->AddEndEvent(endEvent);

		_toolActions.push_back(ToolFront);
		_toolActions.push_back(ToolSide);
		_toolActions.push_back(ToolBack);
	}
#pragma endregion


#pragma region ToolActionFishingPulling
	{
		vector<Vector2> toolFront;
		toolFront.push_back(Vector2(0, 0));

		shared_ptr<Action> ToolFront = make_shared<Action>(toolFront, Action::Type::END, 0.1f);

		vector<Vector2> toolSide;
		toolSide.push_back(Vector2(0, 0));
		toolSide.push_back(Vector2(1, 0));
		shared_ptr<Action> ToolSide = make_shared<Action>(toolSide, Action::Type::END, 0.4f);

		vector<Vector2> toolBack;
		toolBack.push_back(Vector2(0, 0));
		shared_ptr<Action>ToolBack = make_shared<Action>(toolBack, Action::Type::END, 0.1f);

		CallBack endEvent = std::bind(&PlayerImproved::ToolEndEvent, this);

		ToolFront->AddEndEvent(endEvent);
		ToolSide->AddEndEvent(endEvent);
		ToolBack->AddEndEvent(endEvent);

		_toolActions.push_back(ToolFront);
		_toolActions.push_back(ToolSide);
		_toolActions.push_back(ToolBack);
	}
#pragma endregion
}
