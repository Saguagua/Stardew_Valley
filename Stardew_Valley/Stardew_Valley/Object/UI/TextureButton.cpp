#include "framework.h"
#include "TextureButton.h"

TextureButton::TextureButton(wstring path, Vector2 size, CallBack callback)
	:Button(size, callback)
{
	_renderer = make_shared<TextureRect>(path, Vector2(1,1), size); //todo ��ư 2�� �ٿ��� ���� ������ ������ ����
}

void TextureButton::Render()
{
	_col->Render();
	_renderer->Render();
}

void TextureButton::PostRender()
{
	_col->Render();			//�� �� PostRender ��������
	_renderer->Render();
}

void TextureButton::Update()
{
	_col->Update();
	_renderer->Update();
	Button::Update();
}
