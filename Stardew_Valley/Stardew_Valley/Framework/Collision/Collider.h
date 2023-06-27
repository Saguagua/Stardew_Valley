#pragma once
class Collider
{
	enum Type
	{
		NONE,
		CIRCLE,
		RECT
	};

public:
	Collider() {}
	~Collider() {}

	void Update();
	void Render();

	bool IsCollision(shared_ptr<Collider> other);
	virtual bool IsCollision(shared_ptr<class RectCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) abstract;

protected:
	shared_ptr<Transform> _transform = make_shared<Transform>();;
	Collider::Type _type = Type::NONE;
};

