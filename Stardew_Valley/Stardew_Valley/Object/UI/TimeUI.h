#pragma once
class TimeUI
{
public:
	TimeUI();
	~TimeUI() {}

	void Render();
	void Update();

	void SetPos(Vector2 pos) { _bodySlot->SetPos(pos); }
	void SetRotate(float angle) { _rotateSlot->SetAngle(angle); }
private:
	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _rotateSlot;
	shared_ptr<Transform> _hourHandSlot;
	shared_ptr<Sprite> _body;
	shared_ptr<Sprite> _hourHand;
};

