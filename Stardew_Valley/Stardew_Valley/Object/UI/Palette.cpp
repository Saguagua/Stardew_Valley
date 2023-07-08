#include "framework.h"
#include "Palette.h"

Palette::Palette(Vector2 size)
	:_size(size)
{
	_mainWin = make_shared<ColorButton>(PURPLE, _size);
	_list = make_shared<List>(_size * 0.95f, L"Resource/Tile/TileBright.png", Vector2(13, 14));

	_list->SetParent(_mainWin->GetTransform());
	CallBack onEvent = std::bind(&Palette::Move, this);
	_mainWin->SetMouseOnEvent(onEvent);
	CallBackBool onEvent2 = std::bind(&Palette::OnFocus, this, std::placeholders::_1);
	_mainWin->SetMouseOnEvent(onEvent2);
}

void Palette::PostRender()
{
	_mainWin->Render();
	_list->Render();
}

void Palette::Update()
{
	/*if (_mainWin->GetCollider()->IsCollision(S_MOUSE_POS))
		Move();*/
	_mainWin->Update();
	_list->Update();
}

void Palette::Move()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_centerToMouse = S_MOUSE_POS - _mainWin->GetTransform()->GetPos();
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		_mainWin->GetTransform()->SetPos(S_MOUSE_POS - _centerToMouse);
	}
}
