#include "framework.h"
#include "TextureButton.h"

TextureButton::TextureButton(wstring path, Vector2 size)
	:Button(size)
{
	_renderer = ADD_TILE(path, Vector2(1,1), size); //todo ��ư 2�� �ٿ��� ���� ������ ������ ����
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
	_col->Render();			//�� �� PostRender ��������
	_renderer.lock()->Render();
}

void TextureButton::Update()
{
	_col->Update();
	_renderer.lock()->Update();
	Button::Update();
}
