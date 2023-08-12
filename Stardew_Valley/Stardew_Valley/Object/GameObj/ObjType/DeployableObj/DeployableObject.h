#pragma once
class DeployableObject : public GameObject
{
public:
	enum Type
	{
		BREAK = 0,
		PICK = 1,
		LIGHT = 2,
		BOX = 3,
		HOUSE = 4,
		CROP = 5,
		DROP = 6,
		BLOCK = 7,
		BLANK = 8
	};

	DeployableObject(DeployableObject::Type type, string name, Vector2 size = TILE_SIZE);
	virtual ~DeployableObject() {}

	virtual void Interaction() abstract;

	virtual void Spawn(string name, shared_ptr<class SpawnInfo> data) abstract;

	void SetPos(Vector2 pos) { _collider->SetPos(pos); }
	void SetScale(Vector2 scale) { _collider->SetScale(scale); }
	void SetActive(bool active) { _isActive = active; }
	void SetType(DeployableObject::Type type) { _type = type; }

	bool Block(shared_ptr<RectCollider> collider) { return _collider->Block(collider); }

	shared_ptr<RectCollider> GetCollider() { return _collider; }
	Type GetType() { return _type; }
	bool IsCollision(shared_ptr<CircleCollider> collider) { return _collider->IsCollision(collider); }

protected:
	DeployableObject::Type _type;
	shared_ptr<RectCollider> _collider;
};

