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

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->SetFrame(Vector2(i % ));
	}
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
	buttonSize.x = _size.x / frame.x;
	buttonSize.y = _size.y / frame.y;

	Vector2 startPos;
	startPos.y = buttonSize.y * frame.y / 2;
	startPos.x = buttonSize.x * frame.x / 2;

	for (int i = 0; i < frame.y; i++)
	{
		for (int j = 0; j < frame.x; j++)
		{
			shared_ptr<TextureButton> button = make_shared<TextureButton>(path, frame, buttonSize);
			button->GetTransform()->SetPos(Vector2(startPos.x - i * buttonSize.x, startPos.y - j * buttonSize.y));
			button->GetTransform()->SetParent(_mainRect->GetTransform());
			_buttons.push_back(button);
		}
	}

}