#pragma once
class DropItem
{
public:
	DropItem();
	virtual ~DropItem() {}

	void Update();
	void Render();

	void Interaction();
	void AddPos(Vector2 pos) { _collider->AddPos(pos); }
	void Spawn(string name, shared_ptr<SpawnInfo> data);

	shared_ptr<CircleCollider> GetCollider() { return _collider; }
	shared_ptr<CircleCollider> GetArea() { return _dragArea; }
	Vector2 GetWorldPos() { return _collider->GetWorldPos(); }
	bool IsActive() { return _isActive; }

private:
	shared_ptr<CircleCollider> _collider;
	shared_ptr<CircleCollider> _dragArea;
	string _itemName;
	bool _isActive = false;
};

