#include "framework.h"
#include "../Player/PlayerSubscribe.h"
#include "List.h"
#include "ItemSlot.h"

ItemSlot::ItemSlot()
	:List(Vector2(10,1)), PlayerSubscribe(Type::ITEMS)
{	
	_playerInfo = Player::GetInstance()->RequestSubscribe(this);

	_transform = make_shared<Transform>();

	CreateButtons(XMLPATH, 10);

	_buttonSize = Vector2(40, 40);
	Vector2 space = {10, 0};
	_size.x = _buttonSize.x  * _matrix.x + space.x * 11 + 20;
	_size.y = _buttonSize.y * _matrix.y + 25;
	_body = make_shared<Sprite>(XMLPATH, "ItemBar", _size, SpriteType::UI);
	
	Vector2 startPos = -_size * 0.5f;
	startPos.x += 40;
	startPos.y = 0;

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

void ItemSlot::UpdateInfo()
{
	vector<shared_ptr<Item>> items = _playerInfo.lock()->GetItems();

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->SetName(items[i]->GetName());
	}
}

void ItemSlot::CreateButtons(wstring path, int count)
{
	vector<CallBackInt> callbacks = Player::GetInstance()->GetSelectedIndexCallback();
	auto items = _playerInfo.lock()->GetItems();

	for (int i = 0; i < count; i++)
	{
		shared_ptr<TextureButton> button = make_shared<TextureButton>(path, items[i]->GetName(), Vector2(40, 40));
		//button->AddPushEvent(callbacks[i]);
		_buttons.push_back(button);
	}
}


void ItemSlot::Dead()
{
}
