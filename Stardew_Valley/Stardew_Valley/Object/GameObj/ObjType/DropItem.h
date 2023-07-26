#pragma once
class DropItem :public GameObject
{
public:
	DropItem();
	virtual ~DropItem() {}

	void Update();
	void Render();

	shared_ptr<CircleCollider> GetCollider() { return _col; }
	bool IsActive() { return _isActive; }

	virtual void Interaction() {}

	void Spawn(Vector2 pos, int itemCode);
private:
	shared_ptr<CircleCollider> _col;
	bool _isActive;
};

