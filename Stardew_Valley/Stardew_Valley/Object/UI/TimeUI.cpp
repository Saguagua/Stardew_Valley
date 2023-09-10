#include "framework.h"
#include "TimeUI.h"

TimeUI::TimeUI()
{
	_bodySlot = make_shared<Transform>();
	_hourHandSlot = make_shared<Transform>();
	_rotateSlot = make_shared<Transform>();
	_numberSliceSlot = make_shared<Transform>();

	_body = make_shared<Sprite>("DateTime", Vector2(150, 150), SpriteType::UI);
	_hourHand = make_shared<Sprite>("TimePicker", Vector2(25,35), SpriteType::UI);
	_numberSlice = make_shared<Sprite>("T_", Vector2(7,10), SpriteType::UI);

	_hourNum = make_shared<NumberUI>(6, 2, Vector2(30, 30));
	_minutNum = make_shared<NumberUI>(6, 2, Vector2(30, 30));

	_rotateSlot->SetParent(_bodySlot);
	_rotateSlot->SetPos(Vector2(-27, 25));
	_rotateSlot->SetAngle(3.14159);
	_hourHandSlot->SetParent(_rotateSlot);
	_hourHandSlot->SetPos(Vector2(0.0f, 17.5f));
	_numberSliceSlot->SetParent(_bodySlot);
	_numberSliceSlot->SetPos(Vector2(25.0f, -10.0f));

	_hourNum->_originPos = Vector2(10, -10);
	_minutNum->_originPos = Vector2(45, -10);
	_hourNum->_transform->SetParent(_bodySlot);
	_minutNum->_transform->SetParent(_bodySlot);
}

void TimeUI::Render()
{
	_bodySlot->Set_World();
	_body->Render();
	_hourHandSlot->Set_World();
	_hourHand->Render();
	_numberSliceSlot->Set_World();
	_numberSlice->Render();
	_hourNum->Render();
	_minutNum->Render();
}

void TimeUI::Update()
{
	int hour = TIMER->GetHour();
	int minute = TIMER->GetMinute();

	_bodySlot->Update();
	_rotateSlot->Update();
	_hourHandSlot->Update();
	_numberSliceSlot->Update();
	_rotateSlot->AddAngle(-3.14 / 180 * DELTA_TIME); //-3.14 / 180 * 35

	_hourNum->SetNumber(hour);
	_minutNum->SetNumber(minute);
}
