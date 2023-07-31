#include "framework.h"
#include "TextureButton.h"

TextureButton::TextureButton(wstring path, Vector2 size)
	:Button(size)
{
	_renderer = make_shared<TextureRect>(path, Vector2(1, 1), size);
	_renderer->SetCurFrame(0);
}

TextureButton::TextureButton(wstring path, Vector2 clip, Vector2 size)
	: Button(size)
{
	_renderer = make_shared<TextureRect>(path, clip, size);
}

void TextureButton::Render()
{
	_col->Render();
	_renderer->Render();
}

void TextureButton::Update()
{
	_col->Update();
	Button::Update();
}

void TextureButton::SetFrame(Vector2 frame)
{
	_renderer->SetCurFrame(frame);
}

void TextureButton::SetFrame(int index)
{
	_renderer->SetCurFrame(index);
}
