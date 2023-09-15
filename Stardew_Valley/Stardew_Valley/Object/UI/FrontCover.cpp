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
	if (!SCENEMANAGER->_changeScene)
		return;

	_transform->Set_World(0);
	_renderer->Render();
}

void FrontCover::Update()
{
	if (!SCENEMANAGER->_changeScene)
		return;

	float val = 1 * DELTA_TIME;

	if (_darker)
	{
		_color.w += val;
		
		if (_color.w >= 1)
		{
			_color.w = 1.0f;
			_darker = false;
			if (_cb != nullptr)
				_cb();
		}
	}
	else
	{
		_color.w -= val;

		if (_color.w <= 0)
		{
			_color.w = 0.0f;
			_darker = true;
			SCENEMANAGER->_changeScene = false;
		}
	}

	_renderer->SetColor(_color);
}
