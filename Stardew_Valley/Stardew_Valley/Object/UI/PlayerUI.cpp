#include "framework.h"
#include "Window.h"
#include "List.h"
#include "ItemSlot.h"
#include "Palette.h"
#include "BagUI.h"
#include "Bar.h"
#include "PlayerUI.h"

PlayerUI* PlayerUI::_instance = nullptr;

PlayerUI::PlayerUI()
{
	_transform = make_shared<Transform>();
	_bagUI = make_shared<BagUI>();
	_itemSlot = make_shared<ItemSlot>();
	_hpBar = make_shared<Bar>("Resource/UI/UI", "HPBar.png", Vector2(35, 200));
	_staminaBar = make_shared<Bar>("Resource/UI/UI", "StaminaBar.png", Vector2(35, 200));
	_bagUI->SetActive(false);
	_itemSlot->SetActive(true);
	_itemSlot->SetPos(Vector2(0, -300));
	_hpBar->SetPos(Vector2(500, -250));
	_staminaBar->SetPos(Vector2(545, -250));
	_bagUI->SetPos(Vector2(0,0));
	_itemSlot->Update();
	_bagUI->Update();
}

void PlayerUI::PostRender()
{
	_hpBar->Render();
	_staminaBar->Render();
	_itemSlot->Render();
	_bagUI->Render();
}

void PlayerUI::Update()
{
	_bagUI->Update();
	_itemSlot->Update();
	Key();
}

void PlayerUI::SetHP(float hp)
{
	_hpBar->SetRatio(Vector2(1.0f, hp));
}

void PlayerUI::SetStamina(float stamina)
{
	_staminaBar->SetRatio(Vector2(1.0f, stamina));
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
		_bagActive = !_bagActive;
		_itemSlot->SetActive(!_bagActive);
		_bagUI->SetActive(_bagActive);
	}
}