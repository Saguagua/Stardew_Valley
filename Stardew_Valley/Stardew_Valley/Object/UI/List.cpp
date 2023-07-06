#include "framework.h"
#include "List.h"

List::List(Vector2 size, wstring path, Vector2 frame)
	:_size(size)
{
	_mainRect = make_shared<ColorButton>(LIGHTPURPLE, _size);
	
	CreateButtons(path, frame);
}

void List::Render()
{
	_mainRect->Render();

	for (shared_ptr<TextureButton> button : _buttons)
	{
		button->Render();
	}
}

void List::Update()
{
	_mainRect->Update();

	for (shared_ptr<TextureButton> button : _buttons)
	{
		button->Update();
	}
}

void List::KeyInput()
{
}

void List::CreateButtons(wstring path, Vector2 frame)
{
	Vector2 buttonSize;
	buttonSize.x = _size.x / frame.x / 1.125;
	buttonSize.y = _size.y / frame.y;

	Vector2 startPos;
	startPos.x = -buttonSize.x * frame.x / 2- buttonSize.x / 2;
	startPos.y = buttonSize.y * frame.y / 2 - buttonSize.y / 2;

	for (int i = 0; i <= frame.y; i++)
	{
		for (int j = 0; j <= frame.x; j++)
		{
			shared_ptr<TextureButton> button = make_shared<TextureButton>(path, frame, buttonSize);
			button->GetTransform()->SetPos(Vector2(startPos.x + i * (buttonSize.x + 5), startPos.y - j * (buttonSize.y + 5)));
			button->GetTransform()->SetParent(_mainRect->GetTransform());
			button->SetFrame(Vector2(i,j));
			CallBackInt pEvent = std::bind(&List::PushButtonEvent, this, j + i * frame.y);
			button->SetPushEvent(pEvent);
			_buttons.push_back(button);
		}
	}

}

void List::PushButtonEvent(int index)
{
	if (_curIndex != -1)
		_buttons[_curIndex]->GetCollider()->SetDebug(false);
	if (_curIndex == index)
		return;
	_curIndex = index;
	_buttons[_curIndex]->GetCollider()->SetDebug(true);
}
