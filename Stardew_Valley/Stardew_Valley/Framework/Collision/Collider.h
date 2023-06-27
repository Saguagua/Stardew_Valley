#pragma once
class Collider
{
public:
	Collider() {}
	~Collider() {}

	void Update();
	virtual void Render() abstract;

	bool IsCollision(shared_ptr<Collider> other);
	virtual bool IsCollision(shared_ptr<class RectCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) abstract;

	void SetPos(Vector2 pos) {_transform->SetPos(pos);}

protected:
	enum Type
	{
		NONE,
		CIRCLE,
		RECT
	};

	shared_ptr<class ShapeLine> _renderer;
	shared_ptr<Transform> _transform = make_shared<Transform>();
	Collider::Type _type = Type::NONE;

};

