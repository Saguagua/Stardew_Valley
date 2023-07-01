#include "framework.h"
#include "TextureButton.h"

TextureButton::TextureButton(wstring path, Vector2 size, CallBack callback)
	:Button(size, callback)
{
	_renderer = make_shared<TextureRect>(path, Vector2(1,1), size); //todo 버튼 2개 붙여서 누를 때마다 프레임 변경
}

void TextureButton::Render()
{
	_col->Render();
	_renderer->Render();
}

void TextureButton::PostRender()
{
	_col->Render();			//둘 다 PostRender 만들어야함
	_renderer->Render();
}

void TextureButton::Update()
{
	_col->Update();
	_renderer->Update();
	Button::Update();
}
