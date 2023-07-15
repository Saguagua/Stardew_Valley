#pragma once
class CircleCollider : public Collider, enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(float radius);
	virtual ~CircleCollider() {}

	virtual void Render() override;

	void SetColor(XMFLOAT4 color) { _renderer->SetColor(color); }

	virtual bool IsCollision(Vector2 other) override;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;
	
	virtual Vector2 GetWorldPos() override;
	virtual Vector2 GetWorldScale() override;
	float GetRadius() { return _radius; }
	float GetWorldRadius();

private:
	friend RectCollider;

	shared_ptr<CircleLine> _renderer;
	float _radius;
};

