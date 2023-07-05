#include "framework.h"
#include "Button.h"

Button::Button(Vector2 size)
	:_size(size)
{
	_col = make_shared<RectCollider>(_size);
}

void Button::Update()
{
	_col->Update();

	if (_col->IsCollision(W_MOUSE_POS))
	{
		if (_mouseOnEvent != nullptr)
			_mouseOnEvent();
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (_pushEvent != nullptr)
				_pushEvent();
		}
	}
}
