#include "framework.h"
#include "../BasicObj/XMLRect.h"
#include "List.h"
#include "ItemSlot.h"

ItemSlot::ItemSlot()
	:List(Vector2(10,1))
{
	CreateButtons();
	_items = PLAYER->GetItems();
	_buttonSize = _buttons[0]->GetSize();
	Vector2 space = {10, 0};
	_size.x = _buttonSize.x  * _matrix.x + space.x * 11 + 20;
	_size.y = _buttonSize.y * _matrix.y + 25;
	Vector2 startPos = -_size * 0.5f;
	startPos.x += 30;
	startPos.y = 0;
	_transform = make_shared<Transform>();
	_body = make_shared<XMLRect>("Resource/UI/UI", "ItemBar.png", _size);
	SetButtons(startPos, space);
}

void ItemSlot::Update()
{
	if (!_isActive)
		return;

	List::Update();
}

void ItemSlot::PushButtonEvent(int index)
{
	List::PushButtonEvent(index);
}

void ItemSlot::CreateButtons()
{
	Vector2 maxFrame = DATA->GetObjectMaxFrame();
	vector<CallBackInt> callbacks = PLAYER->GetSelectedIndexCallback();

	for (int i = 0; i < 10; i++)
	{
		shared_ptr<TextureButton> button = make_shared<TextureButton>(L"Resource/Object/Objects.png", maxFrame, Vector2(40, 40));
		button->AddPushEvent(callbacks[i]);
		_buttons.push_back(button);
	}
}

void ItemSlot::SetButtons(Vector2 startPos, Vector2 space)
{
	List::SetButtons(startPos, space);

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->SetFrame(_items[i]->GetFrameIndex());
	}
}
