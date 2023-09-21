#include "framework.h"
#include "FrontCover.h"

FrontCover::FrontCover()
{
	_transform = make_shared<Transform>();
	_renderer = make_shared<SingleColorRect>(Vector2(WIN_WIDTH + 10, WIN_HEIGHT + 10), _color);
	_transform->Update();
}

void FrontCover::PostRender()
{
	if (!_isActive)
		return;

	_transform->Set_World(0);
	_renderer->Render();
}

void FrontCover::Update()
{
	if (!_isActive)
		return;

	float val = 1.0f * DELTA_TIME;

	if (_darker)
	{
		_color.w += val;
		
		if (_color.w >= 1)
		{
			_color.w = 1.0f;
			_darker = false;
			if (_cb != nullptr)
				_cb();
			if (_cbInt != nullptr)
				_cbInt(0);
		}
	}
	else
	{
		_color.w -= val;

		if (_color.w <= 0)
		{
			_color.w = 0.0f;
			_darker = true;
			_isActive = false;
		}
	}

	_renderer->SetColor(_color);
}

void FrontCover::FadeStart(CallBack cb, CallBackInt cb2)
{
	_cb = cb;
	_cbInt = cb2;
	_isActive = true;
}
