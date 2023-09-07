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

	struct OBBRectInfo
	{
		Vector2 worldPos;
		Vector2 direction[2]; // 가로 세로 벡터
		float length[2]; // 가로 세로 길이
	};

	RectCollider(Vector2 size);
	~RectCollider() {}

	AABB_Info GetAABB_Info();


	void SetColor(XMFLOAT4 color) { _renderer->SetColor(color); }

	virtual void Render() override;
	
	virtual bool IsCollision(Vector2 other) override;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

	bool Block(shared_ptr<CircleCollider> other);
	bool Block(shared_ptr<RectCollider> other);

	bool OBB(shared_ptr<RectCollider> other);

	OBBRectInfo GetOBBInfo();

	Vector2 GetWorldSize();
	
	void SetSize(Vector2 size);
private:
	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
	{
		float r1 = abs(separate.Dot(e1));
		float r2 = abs(separate.Dot(e2));

		return r1 + r2;
	}


	friend CircleCollider;

	shared_ptr<class RectLine> _renderer;
	Vector2 _size;
};