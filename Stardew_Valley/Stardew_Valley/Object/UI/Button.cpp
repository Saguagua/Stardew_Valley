#include "framework.h"
#include "Button.h"

Button::Button(Vector2 size)
	:_size(size)
{
	_col = make_shared<RectCollider>(_size * 1.1f);
}

void Button::Update()
{

	if (_col->IsCollision(S_MOUSE_POS))
	{
		if (_mouseOnEvent != nullptr)
			_mouseOnEvent();
		if (_mouseOnIntEvent != nullptr)
			_mouseOnIntEvent(0);
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (_pushEvent != nullptr)
				_pushEvent();
			if (_pushIntEvent != nullptr)
				_pushIntEvent(0);
		}
	}
}
