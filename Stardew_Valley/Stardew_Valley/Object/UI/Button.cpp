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
		if (_mouseOnBoolEvent != nullptr)
			_mouseOnBoolEvent(true);
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (_pushEvent != nullptr)
				_pushEvent();
			if (_pushIntEvent != nullptr)
				_pushIntEvent(0);
		}
		if (MOUSE_SCROLL)
		{
			if (_scrollEvent != nullptr)
				_scrollEvent();
		}
	}
	else
	{
		if (_mouseOnBoolEvent != nullptr)
			_mouseOnBoolEvent(false);
	}
}
