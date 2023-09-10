#pragma once
class Effect
{
public:
	Effect(Vector2 size, float timer);
	virtual ~Effect() {}

	void Update();
	void Render();

	void Active(Vector2 pos, float timer);

	Vector2 _size;
	shared_ptr<Transform> _transform;
	float _timer;
	bool _isActive = false;
};

