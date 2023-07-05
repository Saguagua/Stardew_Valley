#include "framework.h"
#include "Palette.h"

Palette::Palette(Vector2 size)
	:_size(size)
{
	_mainWin = make_shared<ColorButton>(PURPLE, _size);
	_list = make_shared<List>(_size, L"Resource/Tile/Tile.png", Vector2(14, 13));
	//_subWin = make_shared<ColorButton>(LIGHTPURPLE, _size);

	//_subWin->GetTransform()->SetScale(Vector2(0.9f, 0.9f));
	//_subWin->GetTransform()->SetPos(-Vector2(0.0, _size.y * 0.02f));
	//_subWin->GetTransform()->SetParent(_mainWin->GetTransform());

	_mainWin->SetMouseOnEvent(std::bind(&Palette::Move, this));
}

void Palette::PostRender()
{
	_mainWin->Render();
	_list->Render();
	//_subWin->Render();
}

void Palette::Update()
{
	_mainWin->Update();
	_list->Update();
	//_subWin->Update();
	//KeyInput();
}

void Palette::KeyInput()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_centerToMouse = W_MOUSE_POS - _mainWin->GetTransform()->GetWorldPos();
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		_mainWin->GetTransform()->SetPos(W_MOUSE_POS - _centerToMouse);
	}
}

void Palette::Move()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_centerToMouse = W_MOUSE_POS - _mainWin->GetTransform()->GetWorldPos();
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		_mainWin->GetTransform()->SetPos(W_MOUSE_POS - _centerToMouse);
	}
}
