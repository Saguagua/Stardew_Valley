#include "framework.h"
#include "TextureButton.h"

TextureButton::TextureButton(wstring path, Vector2 size)
	:Button(size)
{
	_renderer = ADD_TILE(path, Vector2(1,1), size); //todo 버튼 2개 붙여서 누를 때마다 프레임 변경
}

TextureButton::TextureButton(wstring path, Vector2 clip, Vector2 size)
	: Button(size)
{
	_renderer = ADD_TILE(path, clip, size);
}

void TextureButton::Render()
{
	_col->Render();
	_renderer.lock()->Render();
}

void TextureButton::PostRender()
{
	_col->Render();			//둘 다 PostRender 만들어야함
	_renderer.lock()->Render();
}

void TextureButton::Update()
{
	_col->Update();
	_renderer.lock()->Update();
	Button::Update();
}
