#pragma once
class DeployableObject : public GameObject
{
public:
	DeployableObject(ObjectInfo::Type type):GameObject(type) {}
	virtual ~DeployableObject() {}

	virtual void Interaction() abstract;

	virtual void Spawn(string name, SpawnInfo data) abstract;

	void SetPos(Vector2 pos) { _collider->SetPos(pos); }
	void SetScale(Vector2 scale) { _collider->SetScale(scale); }
	void SetActive(bool active) { _isActive = active; }

	shared_ptr<RectCollider> GetCollider() { return _collider; }
	bool IsCollision(shared_ptr<CircleCollider> collider) { return _collider->IsCollision(collider); }
	bool Block(shared_ptr<RectCollider> collider) { return _collider->Block(collider); }
	bool IsActive() { return _isActive; }
protected:
	shared_ptr<RectCollider> _collider;
	bool _isActive;
};

