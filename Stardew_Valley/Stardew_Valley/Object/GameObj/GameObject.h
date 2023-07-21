#pragma once
class GameObject
{
public:
	GameObject(int itemCode);
	~GameObject() {}

	void Update();
	void Render();

	void SetPos(Vector2 pos);
	void SetFrame(Vector2 frame);

	void Spawn(int itemCode, Vector2 pos);

	bool Block(shared_ptr<CircleCollider> other);

protected:
	bool _isActive = false;
	int _itemCode;
};

