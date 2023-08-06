#pragma once
class DropItem :public GameObject
{
public:
	DropItem();
	virtual ~DropItem() {}

	void Update();
	void Render();

	shared_ptr<CircleCollider> GetCollider() { return _col; }
	shared_ptr<CircleCollider> GetArea() { return _dragArea; }
	Vector2 GetWorldPos() { return _col->GetWorldPos(); }
	bool IsActive() { return _isActive; }

	void AddPos(Vector2 pos) { _col->AddPos(pos); }

	virtual void Interaction();

	void Spawn(Vector2 pos, int objCode, int frameIndex, int itemCode);
private:
	shared_ptr<CircleCollider> _col;
	shared_ptr<CircleCollider> _dragArea;
	int _itemCode;
	bool _isActive = false;
};

