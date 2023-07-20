#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject() {}

	void Update();
	void Render();

	void SetPos(Vector2 pos);
	void SetFrame(Vector2 frame);
	bool Block(shared_ptr<CircleCollider> other);

	void Spawn(Vector2 pos, Vector2 frame);

protected:
	bool _isActive = false;
	shared_ptr<CircleCollider> _col;
	shared_ptr<class TextureButton> _body;
};

