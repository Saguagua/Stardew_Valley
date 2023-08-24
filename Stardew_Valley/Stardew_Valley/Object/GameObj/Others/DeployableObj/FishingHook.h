#pragma once
class FishingHook
{
public:
	FishingHook();
	~FishingHook() {}

	void Update();
	void Render(shared_ptr<Sprite> renderer);

	void SetActive(Vector2 originPos, Vector2 dir, float power, float angle);

private:
	void CalculateProjectile();

	shared_ptr<Transform> _transform;
	Vector2 _originPos;
	Vector2 _targetPos;
	Vector2 _dir;
	float _power = 0;
	float _initPower = 0;
	float _angle = 0;
	bool _isActive = false;
};

