#include "framework.h"
#include "PlayerSubscribe.h"
#include "PlayerImproved.h"

PlayerImproved::PlayerImproved()
	:Player()
{
}

void PlayerImproved::Update()
{
	Player::Update();
}

void PlayerImproved::Render()
{
	Player::Render();
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
		_obj->SetImage(_items[_curIndex]->GetName(), _items[_curIndex]->GetIndex());
		armIndex = PlayerAction::HOLD;
	}
	else
	{
		_state &= ~(PlayerState::HOLDING);
		_obj->SetImage("BLANK");
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

	if (type == Item::Type::AXE ||
		type == Item::Type::PICKAXE ||
		type == Item::Type::HOE)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			SetDirection(W_MOUSE_POS);
			SetAction(PlayerAction::TOOL);
			SetArmAction(PlayerAction::TOOL);
			SetPause(true);
		}
		else if (KEY_UP(VK_LBUTTON))
		{
			SetPause(false);
		}
	}
	else if (type == Item::Type::WATERINGCAN)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			SetDirection(W_MOUSE_POS);
			SetAction(PlayerAction::TOOL2);
			SetArmAction(PlayerAction::TOOL2);
			SetPause(true);
		}
		else if (KEY_UP(VK_LBUTTON))
		{
			SetPause(false);
		}
	}
	else if (type == Item::Type::EATABLE)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{

		}
	}
	else if (type == Item::Type::FISHINGROD && FishingSystem::GetInstance()->GetStep() == FishingSystem::Step::THROW)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			SetDirection(W_MOUSE_POS);
			SetAction(PlayerAction::FISHING1);
			SetArmAction(PlayerAction::FISHING1);
			SetPause(true);
		}
		else if (KEY_UP(VK_LBUTTON))
		{
			SetPause(false);
		}
	}
	else if (type == Item::Type::WEAPON)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			SetDirection(W_MOUSE_POS);
			SetAction(PlayerAction::ATTACK);
			SetArmAction(PlayerAction::ATTACK);
			SetFreeze(true);
		}
		
	}
}

void PlayerImproved::SetPause(bool val)
{
	_actions[_actionIndex]->Pause(val);
	_armActions[_armIndex]->Pause(val);
	_freeze = val;
}

void PlayerImproved::SwapItems(int index1, int index2)
{
	shared_ptr<Item> tmp = _items[index1];
	_items[index1] = _items[index2];
	_items[index2] = tmp;

	SendToSubscribers(PlayerSubscribe::Type::ITEMS);
}