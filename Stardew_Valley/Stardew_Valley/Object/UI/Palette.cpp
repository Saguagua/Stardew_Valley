#include "framework.h"
#include "Palette.h"

Palette::Palette(Vector2 size)
	:_size(size)
{
	_mainRect = make_shared<ColorButton>(PURPLE,_size);
	_subRect = make_shared<ColorButton>(LIGHTPURPLE, _size * 0.9);
	_subRect->GetTransform()->SetParent(_mainRect->GetTransform());
	_subRect->GetTransform()->SetPos(Vector2(0, -20));
}

void Palette::PostRender()
{
	_mainRect->Render();
	_subRect->Render();
}

void Palette::Update()
{
	_mainRect->Update();
	_subRect->Update();
}

void Palette::KeyInput()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_centerToMouse = W_MOUSE_POS - _mainRect->GetTransform()->GetWorldPos();
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		_mainRect->GetTransform()->SetPos(W_MOUSE_POS - _centerToMouse);
	}
}
