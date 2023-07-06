#include "framework.h"
#include "ColorButton.h"

ColorButton::ColorButton(XMFLOAT4 color, Vector2 size)
	:Button(size)
{
	_renderer = make_shared<SingleColorRect>(size, color);
}

void ColorButton::Render()
{
	_col->Render();
	_renderer->Render();
}

void ColorButton::Update()
{
	_col->Update();

	Button::Update();
}
