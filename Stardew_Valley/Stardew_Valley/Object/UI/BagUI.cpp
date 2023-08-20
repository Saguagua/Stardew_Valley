#include "framework.h"
#include "../Player/PlayerSubscribe.h"
#include "List.h"
#include "BagUI.h"

BagUI::BagUI()
	:List(Vector2(10, 3)), PlayerSubscribe(Type::ITEMS)
{
	_playerInfo = Player::GetInstance()->RequestSubscribe(this);

	_transform = make_shared<Transform>();
	_objSlot = make_shared<Transform>();

	_body = make_shared<Sprite>(L"Resource/XMLResource.png", "BagUI", Vector2(700, 300));
	_obj = make_shared<Sprite>(L"Resource/XMLResource.png", "BLANK", Vector2(40, 50));

	CreateButtons();

	Vector2 startPos = Vector2(-305, 70);
	Vector2 space = Vector2(50, 75);
	SetButtons(startPos, space);
}

void BagUI::Update()
{
	if (!_isActive)
		return;

	if (_selectedIndex != -1)
	{
		_objSlot->SetPos(S_MOUSE_POS);
		_objSlot->Update();
	}

	List::Update();
}

void BagUI::Render()
{
	if (!_isActive)
		return;


	List::Render();

	if (_selectedIndex != -1)
	{
		_objSlot->Set_World();
		_obj->Render();
	}
}

void BagUI::CreateButtons()
{
	vector<shared_ptr<Item>> items = _playerInfo.lock()->GetItems();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<TextureButton> btn = make_shared<TextureButton>(L"Resource/XMLResource.png", items[i]->GetName(), Vector2(35, 55));
		CallBackInt cb = std::bind(&BagUI::ClickItem, this, i);
		btn->AddPushEvent(cb);
		_buttons.push_back(btn);
	}
}

void BagUI::ClickItem(int index)
{
	if (_selectedIndex == -1 &&
		_buttons[index]->GetName() != "BLANK")
	{
		_selectedIndex = index;
		
	}
	else
	{
		//DATA->SwapItems(_selectedIndex, index);

		_selectedIndex = -1;
	}
}

void BagUI::UpdateInfo()
{
	vector<shared_ptr<Item>> items = _playerInfo.lock()->GetItems();

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->SetName(items[i]->GetName());
	}
}

void BagUI::Dead()
{
}
