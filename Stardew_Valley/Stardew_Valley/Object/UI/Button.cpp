#include "framework.h"
#include "Button.h"

Button::Button(Vector2 size)
	:_size(size)
{
	_col = make_shared<RectCollider>(_size);
}

void Button::Update()
{
	if (_col->IsCollision(S_MOUSE_POS))
	{
		_onFocus = true;

		if (_onEvent != nullptr)
			_onEvent();
		if (_onIntEvent != nullptr)
			_onIntEvent(0);
		if (_onBoolEvent != nullptr)
			_onBoolEvent(true);
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (_pushEvents.size() != 0)
			{
				for (auto cb : _pushEvents)
					cb();
			}
			if (_pushIntEvents.size() != 0)
			{
				for (auto cb : _pushIntEvents)
					cb(0);
			}
			if (_pushBoolEvent != nullptr)
				_pushBoolEvent(false);
		}
		if (MOUSE_SCROLL)
		{
			if (_scrollEvent != nullptr)
				_scrollEvent();
		}
	}
	else
	{
		if (_onBoolEvent != nullptr)
			_onBoolEvent(false);
		_onFocus = false;
	}
}
