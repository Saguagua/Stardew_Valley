#pragma once
class RectCollider : public Collider
{
public:
	struct AABB_Info
	{
		float Up;
		float Down;
		float left;
		float right;
	};

	RectCollider(Vector2 size);
	virtual ~RectCollider() {}

	AABB_Info GetAABB_Info();

	void SetColor(XMFLOAT4 color) { _renderer->SetColor(color); }

	virtual void Render() override;
	
	virtual bool IsCollision(Vector2 other) override;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

	bool Block(shared_ptr<CircleCollider>);
	
private:
	friend CircleCollider;
	friend RectCollider;

	shared_ptr<class RectLine> _renderer;
	Vector2 _size;
};