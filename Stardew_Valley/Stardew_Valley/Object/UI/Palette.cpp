#include "framework.h"
#include "Palette.h"

Palette::Palette(Vector2 size)
	:_size(size)
{
	_mainWin = make_shared<ColorButton>(PURPLE, _size);
	_list = make_shared<List>(_size * 0.9f, L"Resource/Tile/Tile.png", Vector2(13, 14));

	_list->SetParent(_mainWin->GetTransform());
	CallBack onEvent = std::bind(&Palette::Move, this);
	_mainWin->SetMouseOnEvent(onEvent);
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

shared_ptr<TileInfo> Palette::GetCurTileInfo()
{
	return shared_ptr<TileInfo>();
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
