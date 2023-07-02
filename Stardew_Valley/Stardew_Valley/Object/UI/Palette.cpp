#include "framework.h"
#include "Palette.h"

Palette::Palette(Vector2 size)
	:_size(size)
{
	_mainWin = make_shared<Window>(_size, PURPLE);
	_subWin = make_shared<Window>(_size, LIGHTPURPLE);

	_mainWin->AddWindow(_subWin);

	
}

void Palette::PostRender()
{
	_mainWin->Render();
	_subWin->Render();
}

void Palette::Update()
{
	_mainWin->Update();
	_subWin->Update();
}

void Palette::KeyInput()
{
	
}
