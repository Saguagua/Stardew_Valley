#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject() {}

	void Update();
	void Render();

private:
	shared_ptr<CircleCollider> _col;
	shared_ptr<TextureRect> _textureRenderer;
	shared_ptr<RectLine> _lineRenderer;
};

