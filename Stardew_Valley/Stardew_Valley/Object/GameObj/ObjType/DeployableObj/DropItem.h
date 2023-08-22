#pragma once
class DropItem
{
public:
	DropItem();
	~DropItem() {}

	void Update();
	void Render(shared_ptr<Sprite> sprite);

	void Interaction();
	void AddPos(Vector2 pos) { _collider->AddPos(pos); }
	void Spawn(string name, string itemName, Vector2 pos);

	shared_ptr<CircleCollider> GetCollider() { return _collider; }
	Vector2 GetWorldPos() { return _collider->GetWorldPos(); }
	bool IsActive() { return _isActive; }
	bool IsPoping() { return _pop; }

private:
	shared_ptr<CircleCollider> _collider;
	string _name;
	string _itemName;
	bool _isActive = false;

	float _xDir = 0;
	float _power = 50.0f;
	float _maxPower = -50.0f;
	float _range = 10.0f;
	float _speed = 0.5f;
	bool _pop = true;
	bool _up = true;
	Vector2 _tmpPos;
};

