#include "framework.h"
#include "List.h"
#include "../../Data/PlayerInfo.h"
//#include "../../Data/PlayerInfoSubscriber.h"
#include "../BasicObj/XMLRect.h"
#include "BagUI.h"

BagUI::BagUI()
	:List(Vector2(10, 3))
{
	_playerInfo = DATA->GetPlayerInfo();
	_objMaxFrame = DATA->GetObjectMaxFrame();

	_transform = make_shared<Transform>();
	_objSlot = make_shared<Transform>();
	_body = make_shared<XMLRect>("Resource/UI/UI", "BagUI.png", Vector2(700, 300));
	_obj = make_shared<TextureRect>(L"Resource/Object/Objects.png", _objMaxFrame, Vector2(40, 50));

	CreateButtons();

	Vector2 startPos = Vector2(-300, 70);
	Vector2 space = Vector2(57, 75);
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
	vector<shared_ptr<GameObject>> items = _playerInfo->GetItems();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<TextureButton> btn = make_shared<TextureButton>(L"Resource/Object/Objects.png", _objMaxFrame, Vector2(40, 50));
		btn->SetFrame(items[i]->GetFrameIndex());
		CallBackInt cb = std::bind(&BagUI::ClickItem, this, i);
		btn->AddPushEvent(cb);
		_buttons.push_back(btn);
	}
}

void BagUI::ClickItem(int index)
{
	if (_selectedIndex == -1 
		&& _buttons[index]->GetCurFrame() != _objMaxFrame)
	{
		_selectedIndex = index;
		_obj->SetCurFrame(_buttons[index]->GetCurFrame());
	}
	else
	{
		//DATA->SwapItems(_selectedIndex, index);
		vector<shared_ptr<GameObject>>& items = _playerInfo->GetItems();
		shared_ptr<GameObject> tmp = items[index];
		items[index] = items[_selectedIndex];
		items[_selectedIndex] = tmp;

		_buttons[index]->SetFrame(items[index]->GetFrameIndex());
		_buttons[_selectedIndex]->SetFrame(items[_selectedIndex]->GetFrameIndex());

		_selectedIndex = -1;
	}

}

//void BagUI::UpdatePlayerInfo()
//{
//	vector<shared_ptr<GameObject>>& items = _playerInfo->GetItems();
//
//	for (int i = 0; i < _buttons.size(); i++)
//		_buttons[i]->SetFrame(items[i]->GetFrameIndex());
//}
