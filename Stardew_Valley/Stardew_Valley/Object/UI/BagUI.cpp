#include "framework.h"
#include "../GameObj/Creature/Player/Player.h"
#include "../GameObj/Creature/Player/PlayerSubscribe.h"
#include "List.h"
#include "BagUI.h"

BagUI::BagUI(shared_ptr<PlayerImproved> player)
	:List(Vector2(12, 3)), PlayerSubscribe(player, Type::ITEMS)
{
	_transform = make_shared<Transform>();
	_objSlot = make_shared<Transform>();
	
	_number = make_shared<NumberUI>(0, 2, Vector2(20, 20));
	_number->_originPos = Vector2(14, -25);

	_body = make_shared<Sprite>( "BagUI", Vector2(700, 300), SpriteType::UI);
	_obj = make_shared<Sprite>("BLANK", Vector2(40, 50), SpriteType::UI);
	_saleObj = make_shared<Sprite>("BLANK", Vector2(40, 50), SpriteType::UI);

	_saleButton = make_shared<TextureButton>("DialogBoxGreen", Vector2(100, 100));
	
	CallBack cb = std::bind(&BagUI::ClickSaleButton, this);

	_selectedItem = make_shared<Item>();
	_blankItem = make_shared<Item>();
	
	_saleButton->AddPushEvent(cb);

	CreateButtons();

	Vector2 startPos = Vector2(-305, 70);
	Vector2 space = Vector2(50, 75);
	SetButtons(startPos, space);
}

void BagUI::Update()
{
	if (!_isActive)
		return;

	if (_selectedItem->GetName() != "BLANK")
	{
		_objSlot->SetPos(S_MOUSE_POS);
		_objSlot->Update();
	}
	

	List::Update();


	if (_saleMode)
		_saleButton->Update();
}

void BagUI::Render()
{
	if (!_isActive)
		return;

	_transform->Set_World(0);
	_body->Render();

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->PostRender();
		_number->_transform->SetParent(_buttons[i]->GetTransform());
		_number->_transform->Update();
		_number->SetNumber(_player.lock()->GetItem(i)->GetCount());
		_number->Render();
	}

	if (_saleMode)
	{
		_saleButton->Render();
		_saleObj->Render();
	}

	
	_objSlot->Set_World();
	_obj->Render();
}

void BagUI::SetActive(bool val)
{
	_isActive = val;

	if (!_isActive)
	{
		OBJECT_SPAWNER->ActiveDropItem(_selectedItem->GetName(), _player.lock()->GetWorldPos(), _selectedItem->GetCount());
		_selectedItem->SetItem("BLANK", 0);
		_obj->SetImage("BLANK");
	}
}

void BagUI::CreateButtons()
{
	vector<shared_ptr<Item>> items = _player.lock()->GetItems();

	for (int i = 0; i < 36; i++)
	{
		shared_ptr<TextureButton> btn = make_shared<TextureButton>(items[i]->GetName(), Vector2(35, 55));
		CallBackInt cb = std::bind(&BagUI::ClickItem, this, i);
		btn->AddPushEvent(cb);
		_buttons.push_back(btn);
	}
}

void BagUI::ClickItem(int index)
{
	_player.lock()->SwapItems(_selectedItem, _player.lock()->GetItem(index));
	
	_obj->SetImage(_selectedItem->GetName());
}

void BagUI::ClickSaleButton()
{
	if (!_saleMode)
		return;

	if (_selectedItem->GetName() == "BLANK")
	{
		_selectedItem = MONEYMANAGER->Undo();
		
		_obj->SetImage(_selectedItem->GetName());

		auto topItem = MONEYMANAGER->GetTopItem();

		if (topItem != nullptr)
			_saleObj->SetImage(topItem->GetName());
		else
			_saleObj->SetImage("BLANK");
	}
	else
	{
		auto saleInfos = DATA->GetSaleInfos();

		if (saleInfos.count(_selectedItem->GetName()) == 0)
			return;
		
		MONEYMANAGER->SaleItem(_selectedItem);
		_obj->SetImage("BLANK");

		auto topItem = MONEYMANAGER->GetTopItem();

		if (topItem != nullptr)
			_saleObj->SetImage(topItem->GetName());
	}
}

void BagUI::UpdateInfo()
{
	vector<shared_ptr<Item>> items = _player.lock()->GetItems();

	for (int i = 0; i < items.size(); i++)
	{
		_buttons[i]->SetName(items[i]->GetName());
	}
}

void BagUI::Dead()
{
}

void BagUI::SetSaleMode(bool val)
{
	_saleMode = val;

	if (_saleMode)
		_transform->SetPos(Vector2(0, -200));
	else
		_transform->SetPos(Vector2(0, 0));

	_transform->Update();
}
