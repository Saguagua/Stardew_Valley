#include "framework.h"
#include "TextureButton.h"

TextureButton::TextureButton(string name, Vector2 size)
	:Button(size)
{
	_renderer = make_shared<Sprite>(name, size, SpriteType::UI);
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
