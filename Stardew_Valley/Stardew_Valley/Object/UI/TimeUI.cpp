#include "framework.h"
#include "TimeUI.h"

TimeUI::TimeUI(shared_ptr<PlayerImproved> p)
	:PlayerSubscribe(p, PlayerSubscribe::Type::MONEY)
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

	_hourHandSlot->SetParent(_rotateSlot);
	_hourHandSlot->SetPos(Vector2(0.0f, 17.5f));

	_numberSliceSlot->SetParent(_bodySlot);
	_numberSliceSlot->SetPos(Vector2(25.0f, -10.0f));

	_hourNum->_originPos = Vector2(10, -10);
	_minutNum->_originPos = Vector2(55, -10);
	_hourNum->_transform->SetParent(_bodySlot);
	_minutNum->_transform->SetParent(_bodySlot);

	_minuteAngle = 3.141592f / (18 * TIMER->GetMaxMinute());
	_moneyPos = {0,0};
	_datePos = { 0,0 };
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
	
	if (SCENEMANAGER->_cover->IsActive())
		return;
	
	wstring date = _month + L"월 " + _day + L"일";

	Font::GetInstance()->RenderText(date, "Nanum", _datePos);
	Font::GetInstance()->RenderText(_money, "Nanum", _moneyPos);
}

void TimeUI::Update()
{
	int time = _hour * _maxMinute + _minute - 6 * _maxMinute;

	_bodySlot->Update();
	_rotateSlot->Update();
	_hourHandSlot->Update();
	_numberSliceSlot->Update();
	_rotateSlot->SetAngle(3.141592f - _minuteAngle * time);

	_hourNum->SetNumber(_hour);
	_minutNum->SetNumber(_minute);
}

void TimeUI::SetPos(Vector2 pos)
{
	_bodySlot->SetPos(pos);
	UpdateMoney();
}

void TimeUI::UpdateMoney()
{
	_money = to_wstring(MONEYMANAGER->_playerMoney);

	Vector2 pos = _bodySlot->GetPos();

	if (_money.size() == 1)
		_moneyPos.x = WIN_WIDTH * 0.5f + pos.x + 40; //4줄 20 3줄 0 2줄 20 1줄 40
	else if (_money.size() == 2)
		_moneyPos.x = WIN_WIDTH * 0.5f + pos.x + 20;
	else if (_money.size() == 3)
		_moneyPos.x = WIN_WIDTH * 0.5f + pos.x + 0;
	else if (_money.size() == 4)
		_moneyPos.x = WIN_WIDTH * 0.5f + pos.x + 20;

	_moneyPos.y = WIN_HEIGHT * 0.5 - pos.y + 50;
}

void TimeUI::UpdateInfo()
{
	UpdateMoney();
}

void TimeUI::Dead()
{
}

void TimeUI::UpdateDate()
{
	_month = to_wstring(TIMER->GetMonth());
	_day = to_wstring(TIMER->GetDay());

	Vector2 pos = _bodySlot->GetPos();

	if (_month.size() + _day.size() == 2)
		_datePos.x = WIN_WIDTH * 0.5f + pos.x - 40; //40
	else if (_month.size() + _day.size() == 3)
		_datePos.x = WIN_WIDTH * 0.5f + pos.x - 60; //
	else if (_month.size() + _day.size() == 4)
		_datePos.x = WIN_WIDTH * 0.5f + pos.x - 80;

	_datePos.y = WIN_HEIGHT * 0.5 - pos.y - 60;
}
