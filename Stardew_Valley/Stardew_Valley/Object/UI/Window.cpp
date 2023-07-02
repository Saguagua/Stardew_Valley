#include "framework.h"
#include "Window.h"

Window::Window(Vector2 size, XMFLOAT4 color)
	:_size(size)
{
	_col = make_shared<RectCollider>(_size);
	_renderer = make_shared<SingleColorRect>(_size, color);
}

void Window::Render()
{
	_col->Render();
	_renderer->Render();
}

void Window::PostRender()
{
	_col->Render();
	_renderer->Render();

	if (_col->IsCollision(W_MOUSE_POS))
		KeyInput();
}

void Window::Update()
{
	_col->Update();
}

void Window::AddButton(shared_ptr<Button> button)
{
}

void Window::AddWindow(shared_ptr<Window> other)
{
	other->SetScale(Vector2(0.9f, 0.9f));
	other->SetPos( -Vector2(0.0, _size.y * 0.02f));
	other->GetCollider()->GetTransform()->SetParent(_col->GetTransform());
	_windows.push_back(other);
}

void Window::KeyInput()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_centerToMouse = W_MOUSE_POS - _col->GetTransform()->GetWorldPos();
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		_col->GetTransform()->SetPos(W_MOUSE_POS - _centerToMouse);
	}
}
