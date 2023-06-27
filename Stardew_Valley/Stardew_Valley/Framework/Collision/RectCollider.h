#pragma once
class RectCollider : public Collider
{
public:
	RectCollider(Vector2 size);
	virtual ~RectCollider() {}

	virtual void Render() override;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

private:
	friend CircleCollider;

	shared_ptr<class RectLine> _renderer;
	Vector2 _size;
};