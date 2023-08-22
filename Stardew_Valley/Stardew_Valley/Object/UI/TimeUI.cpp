#include "framework.h"
#include "../BasicObj/XMLRect.h"
#include "TimeUI.h"

TimeUI::TimeUI()
{
	_bodySlot = make_shared<Transform>();
	_hourHandSlot = make_shared<Transform>();
	_rotateSlot = make_shared<Transform>();

	_body = make_shared<XMLRect>("Resource/UI/UI", "DateTime.png", Vector2(150, 150));
	_hourHand = make_shared<XMLRect>("Resource/UI/UI", "TimePicker.png", Vector2(25,35));

	_rotateSlot->SetParent(_bodySlot);
	_rotateSlot->SetPos(Vector2(-27, 25));
	_rotateSlot->SetAngle(3.14159);
	_hourHandSlot->SetParent(_rotateSlot);
	_hourHandSlot->SetPos(Vector2(0.0f, 17.5f));
}

void TimeUI::Render()
{
	_bodySlot->Set_World();
	_body->Render();
	_hourHandSlot->Set_World();
	_hourHand->Render();
}

void TimeUI::Update()
{
	_bodySlot->Update();
	_rotateSlot->Update();
	_hourHandSlot->Update();
	_rotateSlot->AddAngle(-3.14 / 180 * DELTA_TIME); //-3.14 / 180 * 35
}
