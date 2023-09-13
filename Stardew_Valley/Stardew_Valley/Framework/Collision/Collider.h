#pragma once
class Collider
{
public:
	Collider() {}
	virtual ~Collider() {}

	void Update();
	virtual void Render() abstract;

	bool IsCollision(shared_ptr<Collider> other);
	virtual bool IsCollision(Vector2 other) abstract;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) abstract;

	void SetPos(Vector2 pos) { _transform->SetPos(pos); }
	void SetScale(Vector2 scale) { _transform->SetScale(scale); }
	void SetAngle(float angle) { _transform->SetAngle(angle); }
	void SetParent(shared_ptr<Transform> other) { _transform->SetParent(other); }

	void AddPos(Vector2 pos) { _transform->AddPos(pos); }
	void AddScale(Vector2 scale) { _transform->AddScale(scale); }
	void AddAngle(float angle) { _transform->AddAngle(angle); }

	shared_ptr<Transform> GetTransform() { return _transform; }
	
	Vector2 GetWorldPos();
	Vector2 GetWorldScale();
	static bool _isDebug;
protected:
	enum class Type
	{
		NONE,
		CIRCLE,
		RECT
	};

	shared_ptr<class ShapeLine> _renderer;
	shared_ptr<Transform> _transform = make_shared<Transform>();
	Collider::Type _type = Collider::Type::NONE;


};