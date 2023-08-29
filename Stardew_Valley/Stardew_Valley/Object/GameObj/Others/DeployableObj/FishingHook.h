#pragma once
class FishingHook
{
public:
	FishingHook();
	~FishingHook() {}

	void Update();
	void Render();

	void Spawn(Vector2 dir, float power);
	
	Vector2 GetWorldPos() { return _transform->GetWorldPos(); }
	void SetPos(Vector2 pos) { _transform->SetPos(pos); }
	void SetActive(bool val) { _isActive = val; }
private:
	void CalculateProjectile();

	shared_ptr<Transform> _transform;
	shared_ptr<Sprite> _renderer;
	Vector2 _originPos;
	Vector2 _dir;
	string _name;

	shared_ptr<Tile> _curTile;

	float _horizontalVelocity = 0.0f;
	float _verticalVelocity = 0.0f;
	float _timeMax;
	float _timeCount;
	float _power = 0;
	float _angle;

	bool _isActive = false;
	bool _isFlying = false;
};

