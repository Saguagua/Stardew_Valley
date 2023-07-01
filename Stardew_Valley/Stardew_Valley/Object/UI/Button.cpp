#include "framework.h"
#include "Button.h"

Button::Button(Vector2 size, CallBack callback)
	:_size(size), _callback(callback)
{
	_col = make_shared<RectCollider>(_size);
}

void Button::Update()
{
	_col->Update();

	if (_col->IsCollision(W_MOUSE_POS))
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (_callback != nullptr)
				_callback();
		}
	}
}
