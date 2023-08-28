#pragma once
class FishingHook
{
public:
	FishingHook();
	~FishingHook() {}

	void Update();
	void Render(shared_ptr<Sprite> renderer);

	void SetActive(Vector2 originPos, Vector2 dir, float power);

private:
	void CalculateProjectile();

	shared_ptr<Transform> _transform;
	Vector2 _originPos;
	Vector2 _dir;
	string _name;
	float _horizontalVelocity = 0.0f;
	float _verticalVelocity = 0.0f;
	float _timeMax;
	float _timeCount;
	float _power = 0;
	float _angle;

	bool _isActive = false;
};

