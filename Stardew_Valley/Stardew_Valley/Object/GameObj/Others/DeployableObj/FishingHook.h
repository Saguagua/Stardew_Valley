#pragma once
class FishingHook
{
public:
	FishingHook();
	~FishingHook() {}

	void Update();
	void Render();

	void Spawn();
	
	Vector2 GetWorldPos() { return _transform->GetWorldPos(); }

	void SetDirection(Vector2 direction) { _dir = direction; }
	void SetPower(float power) { _power = power; }
	void SetPos(Vector2 pos) { _transform->SetPos(pos); }
	void SetActive(bool val) { _isActive = val; }
	void SetReverse(bool val) { _reversing = val; }
	void SetResultName(string result) { _resultName = result; }
private:
	void CalculateProjectile();

	shared_ptr<Action> _action;
	shared_ptr<Transform> _transform;
	shared_ptr<Sprite> _renderer;
	Vector2 _originPos;
	Vector2 _dir;

	string _name;
	string _resultName;

	float _horizontalVelocity = 0.0f;
	float _verticalVelocity = 0.0f;
	float _timeMax;
	float _timeCount;
	float _power = 0; // 초기 속도 700 ~ 300
	float _angle = 60.0 * 3.141592 / 180.0;

	bool _isActive = false;
	bool _isFlying = false;
	bool _reversing = false;
};

