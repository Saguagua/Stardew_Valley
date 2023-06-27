#pragma once
class CircleCollider : public Collider, enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(float radius);
	virtual ~CircleCollider() {}

	virtual void Render() override;

	virtual bool IsCollision(shared_ptr<class RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

private:
	friend RectCollider;

	shared_ptr<class CircleLine> _renderer;
	float _radius;
};

