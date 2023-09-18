#pragma once
class TimeUI :public PlayerSubscribe
{
public:
	TimeUI(shared_ptr<PlayerImproved> p);
	~TimeUI() {}

	void Render();
	void Update();

	void SetPos(Vector2 pos);
	void SetRotate(float angle) { _rotateSlot->SetAngle(angle); }

	void UpdateMoney();

	virtual void UpdateInfo() override;
	virtual void Dead() override;
	void UpdateDate();
private:
	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _rotateSlot;
	shared_ptr<Transform> _hourHandSlot;
	shared_ptr<Transform> _numberSliceSlot;

	Vector2 _datePos;
	Vector2 _moneyPos;
	wstring _money;
	wstring _month;
	wstring _day;

	shared_ptr<Sprite> _body;
	shared_ptr<Sprite> _hourHand;
	shared_ptr<Sprite> _numberSlice;
	shared_ptr<NumberUI> _hourNum;
	shared_ptr<NumberUI> _minutNum;

	float _minuteAngle;
	int& _hour = TIMER->GetHour();
	int& _maxMinute = TIMER->GetMaxMinute();
	int& _minute = TIMER->GetMinute();

	// PlayerSubscribe을(를) 통해 상속됨
};

