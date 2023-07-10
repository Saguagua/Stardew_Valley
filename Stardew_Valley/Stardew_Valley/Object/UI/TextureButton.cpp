#include "framework.h"
#include "TextureButton.h"

TextureButton::TextureButton(wstring path, Vector2 size)
	:Button(size)
{
	_renderer = make_shared<TextureRect>(path, Vector2(1, 1), size);
}

TextureButton::TextureButton(wstring path, Vector2 clip, Vector2 size)
	: Button(size)
{
	_renderer = make_shared<TextureRect>(path, clip, size);
}

void TextureButton::Render()
{
	_col->Render();
	_renderer->SetCurFrame(_curFrame);
	_renderer->Render();
}

void TextureButton::Update()
{
	_col->Update();
	_renderer->Update();
	Button::Update();
}
