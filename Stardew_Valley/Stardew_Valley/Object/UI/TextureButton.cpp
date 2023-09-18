#include "framework.h"
#include "TextureButton.h"

TextureButton::TextureButton(string name, Vector2 size)
	:Button(size)
{
	_renderer = make_shared<Sprite>(name, size, SpriteType::UI);

	_fontWorld.x = WIN_WIDTH * 0.5f + _col->GetWorldPos().x;
	_fontWorld.y = WIN_HEIGHT * 0.5f - _col->GetWorldPos().y;
	_fontPos = { 0,0 };
}

void TextureButton::SetPos(Vector2 pos)
{
	_col->SetPos(pos);
	_col->Update();

	_fontWorld.x = WIN_WIDTH * 0.5f + _col->GetWorldPos().x;
	_fontWorld.y = WIN_HEIGHT * 0.5f - _col->GetWorldPos().y;
}

void TextureButton::Render()
{
	_col->GetTransform()->Set_World();
	_renderer->Render();
	_col->Render();
}

void TextureButton::PostRender()
{
	_col->GetTransform()->Set_World();
	_renderer->Render();
	_col->Render();
	Font::GetInstance()->RenderText(_font, "Nanum", _fontPos + _fontWorld);
}

void TextureButton::Update()
{
	_col->Update();
	Button::Update();
}

string TextureButton::GetName()
{
	return _renderer->GetName();
}

void TextureButton::SetName(string name)
{
	_renderer->SetImage(name);
}

void TextureButton::SetFont(wstring word)
{
	_font = word;
}

void TextureButton::SetFontPos(Vector2 pos)
{
	_fontPos = pos;
}
