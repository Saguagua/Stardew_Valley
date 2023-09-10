#include "framework.h"
#include "List.h"
#include "ItemSlot.h"

ItemSlot::ItemSlot(shared_ptr<PlayerImproved> player)
	:List(Vector2(10,1)), PlayerSubscribe(player, Type::ITEMS)
{	
	_transform = make_shared<Transform>();

	CreateButtons(10);

	_buttonSize = Vector2(40, 40);
	Vector2 space = {10, 0};
	_size.x = _buttonSize.x  * _matrix.x + space.x * 11 + 20;
	_size.y = _buttonSize.y * _matrix.y + 25;
	_body = make_shared<Sprite>("ItemBar", _size, SpriteType::UI);
	
	Vector2 startPos = -_size * 0.5f;
	startPos.x += 40;
	startPos.y = 0;

	SetButtons(startPos, space);

	_number = make_shared<NumberUI>(0, 2, Vector2(20, 20));
	_number->_originPos = Vector2(15, -15);
}

void ItemSlot::Update()
{
	if (!_isActive)
		return;

	List::Update();
}

void ItemSlot::Render()
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
}

void ItemSlot::PushButtonEvent(int index)
{
	List::PushButtonEvent(index);
}

void ItemSlot::UpdateInfo()
{
	vector<shared_ptr<Item>> items = _player.lock()->GetItems();

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->SetName(items[i]->GetName());
	}
}

void ItemSlot::CreateButtons(int count)
{
	//vector<CallBackInt> callbacks = _player.lock()->GetSelectedIndexCallback();
	auto items = _player.lock()->GetItems();

	for (int i = 0; i < count; i++)
	{
		shared_ptr<TextureButton> button = make_shared<TextureButton>(items[i]->GetName(), Vector2(40, 40));
		//button->AddPushEvent(callbacks[i]);
		_buttons.push_back(button);
	}
}

void ItemSlot::Dead()
{
}
