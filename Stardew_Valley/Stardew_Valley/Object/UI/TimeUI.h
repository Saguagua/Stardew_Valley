#pragma once
class TimeUI
{
public:
	TimeUI();
	~TimeUI() {}

	void Render();
	void Update();

	void SetPos(Vector2 pos) { _bodySlot->SetPos(pos); }

private:
	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _rotateSlot;
	shared_ptr<Transform> _hourHandSlot;
	shared_ptr<class XMLRect> _body;
	shared_ptr<class XMLRect> _hourHand;
};

