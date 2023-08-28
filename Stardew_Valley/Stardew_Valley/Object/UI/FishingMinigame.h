#pragma once
class FishingMinigame
{
public:
	FishingMinigame();
	~FishingMinigame();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _bodySlot; }
	void SetPos(Vector2 pos) { _bodySlot->SetPos(pos); }
	void SetActive(bool val);
private:
	void KeyInput();

	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _guageSlot;
	shared_ptr<RectCollider> _fishSlot;
	shared_ptr<RectCollider> _cursorSlot;

	shared_ptr<Sprite> _body;
	shared_ptr<Sprite> _fish;
	shared_ptr<SingleColorRect> _guage;
	shared_ptr<SingleColorRect> _cursor;

	bool _isActive = false;

	float _fishPower = 0.0f;
	float _fishCount = 0.0f;
	Vector2 _fishDirection;

	float _power = 0.0f;
	float _maxPower = -500.0f;
	float _percent = 90.0f;
};

