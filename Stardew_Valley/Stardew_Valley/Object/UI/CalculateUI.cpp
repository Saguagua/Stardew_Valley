#include "framework.h"
#include "CalculateUI.h"

CalculateUI::CalculateUI(wstring typeName, Vector2 size)
	:_typeName(typeName)
{
	_body = make_shared<Sprite>("TextBox", size, SpriteType::UI);

	_bodySlot = make_shared<Transform>();
	
	_fontWorld.x = WIN_WIDTH * 0.5f;
	_fontWorld.y = -WIN_HEIGHT * 0.5f;

	_typePos = Vector2(-190, -10);
	_pricePos = Vector2(170, -10);
	_goldPos = Vector2(190, 0);
}

void CalculateUI::Render()
{
	_bodySlot->Set_World();
	_body->Render();
}

void CalculateUI::PostRender()
{
	_bodySlot->Set_World();
	_body->Render();

	Font::GetInstance()->RenderText(_typeName, "Nanum", _typePos + _fontWorld);
	Font::GetInstance()->RenderText(_price, "Nanum", _pricePos + _fontWorld);
	Font::GetInstance()->RenderText(L"G", "Nanum", _goldPos + _fontWorld);
}

void CalculateUI::Update()
{
	_bodySlot->Update();
}

void CalculateUI::SetPrice(short cost)
{
	_price = std::to_wstring(cost);

	if (_price.size() == 1)
		_pricePos = Vector2(170, -10);

	else if (_price.size() == 2)
		_pricePos = Vector2(150, -10);

	else if (_price.size() == 3)
		_pricePos = Vector2(130, -10);


	else if (_price.size() == 4)
		_pricePos = Vector2(110, -10);
}

void CalculateUI::SetPos(Vector2 pos)
{
	_bodySlot->SetPos(pos);
	_fontWorld.x = WIN_WIDTH * 0.5f + pos.x;
	_fontWorld.y = WIN_HEIGHT * 0.5f - pos.y;
}
