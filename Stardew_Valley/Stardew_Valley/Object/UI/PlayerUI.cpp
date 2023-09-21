#include "framework.h"
#include "List.h"
#include "ItemSlot.h"
#include "Palette.h"
#include "BagUI.h"
#include "Bar.h"
#include "TimeUI.h"
#include "../Scene/TestScene/TestScene.h"
#include "PlayerUI.h"

PlayerUI* PlayerUI::_instance = nullptr;

PlayerUI::PlayerUI(shared_ptr<PlayerImproved> player)
	:_player(player)
{
	_transform = make_shared<Transform>();
	_bagUI = make_shared<BagUI>(player);
	_itemSlot = make_shared<ItemSlot>(player);
	_timeUI = make_shared<TimeUI>(player);
	_hpBar = make_shared<Bar>(player, "HPBar", Vector2(35, 200));
	_staminaBar = make_shared<Bar>(player, "StaminaBar", Vector2(35, 200));

	_itemSlot->SetPos(Vector2(0, -300));
	_hpBar->SetPos(Vector2(500, -250));
	_staminaBar->SetPos(Vector2(545, -250));
	_timeUI->SetPos(Vector2(500, 250));
	
	_bagUI->SetActive(false);
	_itemSlot->SetActive(true);
}

void PlayerUI::PostRender()
{
	_hpBar->Render();
	_staminaBar->Render();
	_itemSlot->Render();
	_bagUI->Render();
	_timeUI->Render();
}

void PlayerUI::Update()
{
	Key();
	_bagUI->Update();
	_itemSlot->Update();
	_timeUI->Update();
}

void PlayerUI::NextDay()
{
	_timeUI->SetRotate(3.14159f);
	_timeUI->UpdateDate();
}

void PlayerUI::SetHP(float hp)
{
	_hpBar->SetRatio(Vector2(1.0f, hp));
}

void PlayerUI::SetStamina(float stamina)
{
	_staminaBar->SetRatio(Vector2(1.0f, stamina));
}

void PlayerUI::SetBagMode(bool val)
{
	_bagActive = val;
	_itemSlot->SetActive(!_bagActive);
	_bagUI->SetActive(_bagActive);
}

void PlayerUI::SetSaleMode(bool val)
{
	SetBagMode(val);
	_bagUI->SetSaleMode(val);
}

bool PlayerUI::AddItem(string itemName)
{
	if (_player.lock()->AddItem(itemName))
	{
		_player.lock()->PlayAction(Player::PlayerAction::FISHING3);
		return true;
	}
	return false;
}

void PlayerUI::Key()
{
	if (KEY_DOWN('1'))
	{
		_itemSlot->PushButtonEvent(0);
	}
	else if (KEY_DOWN('2'))
	{
		_itemSlot->PushButtonEvent(1);
	}
	else if (KEY_DOWN('3'))
	{
		_itemSlot->PushButtonEvent(2);
	}
	else if (KEY_DOWN('4'))
	{
		_itemSlot->PushButtonEvent(3);
	}
	else if (KEY_DOWN('5'))
	{
		_itemSlot->PushButtonEvent(4);
	}
	else if (KEY_DOWN('6'))
	{
		_itemSlot->PushButtonEvent(5);
	}
	else if (KEY_DOWN('7'))
	{
		_itemSlot->PushButtonEvent(6);
	}
	else if (KEY_DOWN('8'))
	{
		_itemSlot->PushButtonEvent(7);
	}
	else if (KEY_DOWN('9'))
	{
		_itemSlot->PushButtonEvent(8);
	}
	else if (KEY_DOWN('0'))
	{
		_itemSlot->PushButtonEvent(9);
	}
	else if (KEY_DOWN('E'))
	{
		if (!_bagUI->GetSaleMode())
			SetBagMode(!_bagActive);
	}
}
