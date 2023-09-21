#include "framework.h"
#include "PlayerSubscribe.h"
#include "PlayerImproved.h"

PlayerImproved::PlayerImproved()
	:Player()
{
	_centerSlot = make_shared<Transform>();
	_handSlot = make_shared<Transform>();
	_itemSlot = make_shared<Transform>();
	_itemRenderer = make_shared<Sprite>("BLANK", Vector2(30, 30), SpriteType::OBJECT);
	_weaponCollider = make_shared<RectCollider>(Vector2(20.0f, 40.0f));

	_centerSlot->SetParent(_col->GetTransform());

	_weaponCollider->SetPos(Vector2(0.0f, -20.0f));
	_weaponCollider->SetParent(_handSlot);

	_handSlot->AddPos(Vector2(0, 30));
	_handSlot->SetParent(_centerSlot);


	_itemSlot->AddPos(Vector2(0, 10));
	_itemSlot->SetParent(_handSlot);
	CreateAction();

	_cb = std::bind(&PlayerImproved::Return, this);
}

void PlayerImproved::Initialize()
{
	for (auto item : _items)
		item->SetPlayer(shared_from_this());
}

void PlayerImproved::Update()
{
	Player::Update();

	if (_state & PlayerState::DEAD)
		return;

	_centerSlot->Update();
	_handSlot->Update();
	_itemSlot->Update();
	_weaponCollider->Update();
	if (_toolActive)
	{
		if (!_toolActions[_itemActionIndex]->IsPlay())
			return;

		_toolActions[_itemActionIndex]->Update();
		_itemRenderer->SetIndex(_toolActions[_itemActionIndex]->GetCurFrame().x);
		
		UpdateCenterSlot();
		UpdateHandSlot();
	}
}

void PlayerImproved::Render()
{
	if (_direction == BACK)
	{
		if (_toolActive || (_state & PlayerState::HOLDING))
		{
			_itemSlot->Set_World(0);

			_itemRenderer->Render();
			if (_isAttacking)
				_weaponCollider->Render();
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


		if (_toolActive || (_state & PlayerState::HOLDING))
		{
			_itemSlot->Set_World(0);

			_itemRenderer->Render();
			if (_isAttacking)
				_weaponCollider->Render();
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
	if (_state == PlayerState::DEAD)
		return;

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
		if (type == PlayerSubscribe::Type::ALL ||
			subscriber->_type == type)
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
		_centerSlot->SetAngle(0);
		_handSlot->SetScale(Vector2(1,1));
		_handSlot->SetAngle(0);
		_handSlot->SetPos(Vector2(0, 30));
		_itemSlot->SetAngle(0);
		_itemSlot->SetPos(Vector2(0, 25));
		_itemRenderer->SetImage(_items[_curIndex]->GetName());
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
#pragma region AxePickAxeHoe
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
				_centerSlot->SetAngle(0);
				_centerSlotRotate = 0.0f;
				_centerSlotDirection = { 0, 0 };

				name += "F";
				_itemActionIndex = 0;
				_handSlot->SetPos(Vector2(-10, 20));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 50, -50 };
				_handSlotRotate = 0.0f;

				_itemSlot->SetPos(Vector2(0, 10));
				_itemSlot->SetAngle(0);
			}
			else if (_direction == SIDE)
			{
				_centerSlot->SetAngle(0);
				_centerSlotRotate = 0.0f;
				_centerSlotDirection = { 0, 0 };

				name += "S";
				_itemActionIndex = 1;
				_handSlot->SetPos(Vector2(-10, 20));
				_handSlot->SetAngle(0.7f);
				_handSlotDirection = { 80, -40 };
				_handSlotRotate = -6.5f;

				_itemSlot->SetPos(Vector2(0, 10));
				_itemSlot->SetAngle(0);
			}
			else
			{
				_centerSlot->SetAngle(0);
				_centerSlotRotate = 0.0f;
				_centerSlotDirection = { 0, 0 };

				name += "B";
				_itemActionIndex = 0;
				_handSlot->SetPos(Vector2(0, 20));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 0, 50 };
				_handSlotRotate = 0.0f;

				_itemSlot->SetPos(Vector2(0, 10));
				_itemSlot->SetAngle(0);
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
#pragma endregion
#pragma region WateringCan
	case Item::Type::WATERINGCAN:
	{
		if (KEY_DOWN(VK_LBUTTON) && !_freeze)
		{
			string name = _items[_curIndex]->GetName();

			SetDirection(W_MOUSE_POS);

			if (_direction == FRONT)
			{
				_centerSlot->SetAngle(0);
				_centerSlotRotate = 0.0f;
				_centerSlotDirection = { 0, 0 };

				name += "F";
				_itemActionIndex = 2;
				_handSlot->SetPos(Vector2(0, -20));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 0, 35 };
				_handSlotRotate = 0.0f;

				_itemSlot->SetPos(Vector2(0, 5));
				_itemSlot->SetAngle(0);
			}
			else if (_direction == SIDE)
			{
				_centerSlot->SetAngle(0);
				_centerSlotRotate = 0.0f;
				_centerSlotDirection = { 0, 0 };

				name += "S";
				_itemActionIndex = 3;
				_handSlot->SetPos(Vector2(20, -10));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 0, 20 };
				_handSlotRotate = 0.0f;

				_itemSlot->SetPos(Vector2(5, 5));
				_itemSlot->SetAngle(0);
			}
			else
			{
				_centerSlot->SetAngle(0);
				_centerSlotRotate = 0.0f;
				_centerSlotDirection = { 0, 0 };

				name += "B";
				_itemActionIndex = 4;
				_handSlot->SetPos(Vector2(0, 0));
				_handSlot->SetAngle(0);
				_handSlotDirection = { 0, 35 };
				_handSlotRotate = 0.0f;

				_itemSlot->SetPos(Vector2(0, 5));
				_itemSlot->SetAngle(0);
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
#pragma endregion
#pragma region Eatable
	case Item::Type::EATABLE:
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			_centerSlot->SetAngle(0);
			_centerSlotRotate = 0.0f;
			_centerSlotDirection = { 0, 0 };

			_handSlot->SetPos(Vector2(0, 20));
			_handSlot->SetAngle(0);
			_handSlotDirection = { 0, 0 };
			_handSlotRotate = 0.0f;

			_itemActionIndex = 1;
			SetAction(PlayerAction::EAT);
			SetArmAction(PlayerAction::EAT);
			_toolActions[_itemActionIndex]->Play();

			_toolActive = true;
			_freeze = true;
		}
		break;
	}
#pragma endregion
#pragma region FishingRod
	case Item::FISHINGROD:
	{
		auto step = FishingSystem::GetInstance()->GetStep();

		if (step == FishingSystem::Step::THROW) 
		{
			if (KEY_DOWN(VK_LBUTTON))
			{
				string name = _items[_curIndex]->GetName();

				SetDirection(W_MOUSE_POS);

				if (_direction == FRONT)
				{
					_centerSlot->SetAngle(0);
					_centerSlotRotate = 0.0f;
					_centerSlotDirection = { 0, 0 };

					name += "F";
					_itemActionIndex = 0;
					_handSlot->SetPos(Vector2(-10, 20));
					_handSlot->SetAngle(0);
					_handSlotDirection = { 50, -50 };
					_handSlotRotate = 0.0f;

					_itemSlot->SetPos(Vector2(0, 0));
					_itemSlot->SetAngle(0);
				}
				else if (_direction == SIDE)
				{
					_centerSlot->SetAngle(0);
					_centerSlotRotate = 0.0f;
					_centerSlotDirection = { 0, 0 };

					name += "S";
					_itemActionIndex = 1;
					_handSlot->SetPos(Vector2(-20, 35));
					_handSlot->SetAngle(0.3f);
					_handSlotDirection = { 200, -25 };
					_handSlotRotate = -10.0f;

					_itemSlot->SetPos(Vector2(5, 0));
					_itemSlot->SetAngle(0);
				}
				else
				{
					_centerSlot->SetAngle(0);
					_centerSlotRotate = 0.0f;
					_centerSlotDirection = { 0, 0 };

					name += "F";
					_itemActionIndex = 0;
					_handSlot->SetPos(Vector2(0, 30));
					_handSlot->SetAngle(0);
					_handSlotDirection = { 0, 50 };
					_handSlotRotate = 0.0f;

					_itemSlot->SetPos(Vector2(0, 0));
					_itemSlot->SetAngle(0);
				}

				_itemRenderer->SetImage(name);

				_handSlot->SetScale(DATA->GetXMLInfo(name)->GetSize(0));

				SetAction(PlayerAction::FISHING1);
				SetArmAction(PlayerAction::FISHING1);
				_toolActions[_itemActionIndex]->Play();

				_toolActive = true;
				_freeze = true;
				SetPause(true);

				_items[_curIndex]->StartCharging(300, 0, 700, 5);
			}
			else if (KEY_PRESS(VK_LBUTTON))
			{
				_items[_curIndex]->Charging();
			}
			else if (KEY_UP(VK_LBUTTON))
			{
				SetPause(false);
			}
		}
		else if (step == FishingSystem::Step::HOLD)
		{
			_handSlot->SetPos(Vector2(-10, 10));
		}
		break;
	}
#pragma endregion
#pragma region weapon
	case Item::Type::WEAPON:
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			SetDirection(W_MOUSE_POS);

			if (_direction == FRONT)
			{
				_itemActionIndex = 12;

				_centerSlot->SetAngle(XM_PIDIV2);
				_centerSlotRotate = -10.0f;
				_centerSlotDirection = { 0, 0 };

				_handSlot->SetPos(Vector2(0.0f, -20.0f));
				_handSlot->SetAngle(0);
				_handSlotRotate = 0.0f;
				_handSlotDirection = { 0, 0 };

				_itemSlot->SetPos(Vector2(0, 0));
				_itemSlot->SetAngle(-105.0f * XM_PI / 180.0f);
			}
			else if (_direction == SIDE)
			{
				_itemActionIndex = 13;

				_centerSlot->SetAngle(XM_PI);
				_centerSlotRotate = -10.0f;
				_centerSlotDirection = { 0, 0 };

				_handSlot->SetPos(Vector2(0.0f, -20.0f));
				_handSlot->SetAngle(0);
				_handSlotRotate = 0.0f;
				_handSlotDirection = { 0, 0 };

				_itemSlot->SetPos(Vector2(0, 0));
				_itemSlot->SetAngle(-105.0f * XM_PI / 180.0f);
				
			}
			else
			{
				_itemActionIndex = 14;

				_centerSlot->SetAngle(-XM_PIDIV2);
				_centerSlotRotate = -10.0f;
				_centerSlotDirection = { 0, 0 };

				_handSlot->SetPos(Vector2(0.0f, -20.0f));
				_handSlot->SetAngle(0);
				_handSlotRotate = 0.0f;
				_handSlotDirection = { 0, 0 };

				_itemSlot->SetPos(Vector2(0, 0));
				_itemSlot->SetAngle(-105.0f * XM_PI / 180.0f);
			}

			_itemRenderer->SetImage(_items[_curIndex]->GetName());

			_toolActions[_itemActionIndex]->Play();
			SetAction(PlayerAction::ATTACK);
			SetArmAction(PlayerAction::ATTACK);

			SetFreeze(true);
			_isAttacking = true;
			_toolActive = true;
		}
		break;
	}
#pragma endregion
#pragma region SeedFacility
	case Item::Type::SEED:
	case Item::Type::FACILITY:
	{
		if (KEY_DOWN(VK_LBUTTON))
			_items[_curIndex]->Use();
		break;
	}
#pragma endregion
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

void PlayerImproved::UpdateCenterSlot()
{
	_centerSlot->AddPos(_centerSlotDirection * DELTA_TIME);
	_centerSlot->AddAngle(_centerSlotRotate * DELTA_TIME);
}

void PlayerImproved::SwapItems(shared_ptr<Item> item1, shared_ptr<Item> item2)
{
	shared_ptr<Item> tmp = make_shared<Item>();

	tmp->Copy(item1);

	item1->Copy(item2);

	item2->Copy(tmp);
	
	SendToSubscribers(PlayerSubscribe::Type::ITEMS);
}

void PlayerImproved::ToolEndEvent()
{
	_items[_curIndex]->Use();
}

void PlayerImproved::DeathEvent()
{
	SCENEMANAGER->_cover->FadeStart(_cb, nullptr);

	DungeonSystem::GetInstance()->_active = false;

	_hp = _maxHp;
	_stamina = _maxStamina;
}

void PlayerImproved::Return()
{
	_map.lock()->ChangeMap(3);
	_col->SetPos(Vector2(200, 40));
	_col->Update();
	SCENEMANAGER->ChangeScene(SceneManager::DAYEND);
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
		Kill();
		
	float ratio = (float)_hp / (float)_maxHp;
	PlayerUI::GetInstance()->SetHP(ratio);
}

void PlayerImproved::AddStamina(short cost)
{
	_stamina += cost;

	if (_stamina <= 0)
		Kill();

	float ratio = (float)_stamina / (float)_maxStamina;
	PlayerUI::GetInstance()->SetStamina(ratio);
}


void PlayerImproved::Kill()
{
	_state = PlayerState::DEAD;
	PlayAction(PlayerAction::DEATH);
}

void PlayerImproved::CreateAction()
{

#pragma region Attack
	//FrontAttack
	{
		CallBack cb = std::bind(&PlayerImproved::SetIdle, this);
		CallBackBool cbb = std::bind(&PlayerImproved::SetFreeze, this, false);
		CallBackBool cbb2 = std::bind(&PlayerImproved::SetAttacking, this, false);

		vector<Vector2> frontBody;
		frontBody.push_back(Vector2(0, 4));
		frontBody.push_back(Vector2(1, 4));
		frontBody.push_back(Vector2(2, 4));
		frontBody.push_back(Vector2(3, 4));
		frontBody.push_back(Vector2(4, 4));
		frontBody.push_back(Vector2(5, 4));

		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::END, 0.05f);
		FrontBody->AddEndEvent(cb);
		FrontBody->SetEndBoolEvent(cbb);
		FrontBody->SetEndBoolEvent(cbb2);

		_actions.push_back(FrontBody);

		vector<Vector2> frontArm;
		frontArm.push_back(Vector2(12, 4));
		frontArm.push_back(Vector2(13, 4));
		frontArm.push_back(Vector2(14, 4));
		frontArm.push_back(Vector2(15, 4));
		frontArm.push_back(Vector2(16, 4));
		frontArm.push_back(Vector2(17, 4));

		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END, 0.05f);

		_armActions.push_back(FrontArm);
	}

	//SideAttack
	{
		CallBack cb = std::bind(&PlayerImproved::SetIdle, this);
		CallBackBool cbb = std::bind(&PlayerImproved::SetFreeze, this, false);
		CallBackBool cbb2 = std::bind(&PlayerImproved::SetAttacking, this, false);

		vector<Vector2> sideBody;
		sideBody.push_back(Vector2(0, 5));
		sideBody.push_back(Vector2(1, 5));
		sideBody.push_back(Vector2(2, 5));
		sideBody.push_back(Vector2(3, 5));
		sideBody.push_back(Vector2(4, 5));
		sideBody.push_back(Vector2(5, 5));

		shared_ptr<Action> SideBody = make_shared<Action>(sideBody, Action::Type::END, 0.05f);

		SideBody->AddEndEvent(cb);
		SideBody->SetEndBoolEvent(cbb);
		SideBody->SetEndBoolEvent(cbb2);


		_actions.push_back(SideBody);

		vector<Vector2> sideArm;
		sideArm.push_back(Vector2(12, 5));
		sideArm.push_back(Vector2(13, 5));
		sideArm.push_back(Vector2(14, 5));
		sideArm.push_back(Vector2(15, 5));
		sideArm.push_back(Vector2(16, 5));
		sideArm.push_back(Vector2(17, 5));

		shared_ptr<Action> SideArm = make_shared<Action>(sideArm, Action::Type::END, 0.05f);

		_armActions.push_back(SideArm);
	}

	//BackAttack
	{
		CallBack cb = std::bind(&PlayerImproved::SetIdle, this);
		CallBackBool cbb = std::bind(&PlayerImproved::SetFreeze, this, false);
		CallBackBool cbb2 = std::bind(&PlayerImproved::SetAttacking, this, false);

		vector<Vector2> backBody;
		backBody.push_back(Vector2(0, 6));
		backBody.push_back(Vector2(1, 6));
		backBody.push_back(Vector2(2, 6));
		backBody.push_back(Vector2(3, 6));
		backBody.push_back(Vector2(4, 6));
		backBody.push_back(Vector2(5, 6));

		shared_ptr<Action> BackBody = make_shared<Action>(backBody, Action::Type::END, 0.05f);

		BackBody->AddEndEvent(cb);
		BackBody->SetEndBoolEvent(cbb);
		BackBody->SetEndBoolEvent(cbb2);

		_actions.push_back(BackBody);

		vector<Vector2> backArm;
		backArm.push_back(Vector2(12, 6));
		backArm.push_back(Vector2(13, 6));
		backArm.push_back(Vector2(14, 6));
		backArm.push_back(Vector2(15, 6));
		backArm.push_back(Vector2(16, 6));
		backArm.push_back(Vector2(17, 6));

		shared_ptr<Action> BackArm = make_shared<Action>(backArm, Action::Type::END, 0.05f);

		_armActions.push_back(BackArm);
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


#pragma region Eat

	{
		CallBack cb = std::bind(&PlayerImproved::SetIdle, this);
		CallBackBool cbb = std::bind(&PlayerImproved::SetFreeze, this, false);
		CallBackBool cbb2 = std::bind(&PlayerImproved::SetAttacking, this, false);

		vector<Vector2> frontBody;
		frontBody.push_back(Vector2(2, 16));
		frontBody.push_back(Vector2(3, 16));
		frontBody.push_back(Vector2(4, 16));
		frontBody.push_back(Vector2(0, 17));
		frontBody.push_back(Vector2(1, 17));

		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::END, 0.2f);
		FrontBody->AddEndEvent(cb);

		_actions.push_back(FrontBody);
		_actions.push_back(FrontBody);
		_actions.push_back(FrontBody);

		vector<Vector2> frontArm;
		frontArm.push_back(Vector2(6, 16));
		frontArm.push_back(Vector2(7, 16));
		frontArm.push_back(Vector2(7, 16));
		frontArm.push_back(Vector2(6, 17));
		frontArm.push_back(Vector2(7, 17));

		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END, 0.2f);

		_armActions.push_back(FrontArm);
		_armActions.push_back(FrontArm);
		_armActions.push_back(FrontArm);
	}

#pragma endregion

#pragma region Death
	{
		CallBack cb = std::bind(&PlayerImproved::DeathEvent, this);
		vector<Vector2> frontBody;
		frontBody.push_back(Vector2(4, 0));
		frontBody.push_back(Vector2(5, 0));

		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::END, 0.2f);
		FrontBody->AddEndEvent(cb);

		_actions.push_back(FrontBody);
		_actions.push_back(FrontBody);
		_actions.push_back(FrontBody);

		vector<Vector2> frontArm;
		frontArm.push_back(Vector2(10, 0));
		frontArm.push_back(Vector2(11, 0));

		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END, 0.2f);

		_armActions.push_back(FrontArm);
		_armActions.push_back(FrontArm);
		_armActions.push_back(FrontArm);
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
		shared_ptr<Action> ToolSide = make_shared<Action>(toolSide, Action::Type::END, 0.2f);

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
		shared_ptr<Action> ToolSide = make_shared<Action>(toolSide, Action::Type::END, 0.05f);

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
		shared_ptr<Action> ToolSide = make_shared<Action>(toolSide, Action::Type::END, 0.1f);

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


#pragma region ToolWeaponAttack
	{
		vector<Vector2> toolFront;
		toolFront.push_back(Vector2(0, 0));

		shared_ptr<Action> ToolFront = make_shared<Action>(toolFront, Action::Type::END, 0.3f);

		vector<Vector2> toolSide;
		toolSide.push_back(Vector2(0, 0));
		shared_ptr<Action> ToolSide = make_shared<Action>(toolSide, Action::Type::END, 0.3f);

		vector<Vector2> toolBack;
		toolBack.push_back(Vector2(0, 0));
		shared_ptr<Action>ToolBack = make_shared<Action>(toolBack, Action::Type::END, 0.3f);

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
