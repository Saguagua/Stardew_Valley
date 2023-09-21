#pragma once
class Effect
{
public:
	Effect(Vector2 size, float timer);
	virtual ~Effect() {}

	void Update();
	void Render();

	void SetAction(shared_ptr<Action> action) { _action = action; }

	void SetImage(string name, int index = 0);

	void Active(Vector2 pos, float timer);

	float _timer;
	bool _isActive = false;

protected:
	shared_ptr<Transform> _transform;

	shared_ptr<Action> _action;
	Vector2 _size;
private:
	shared_ptr<Sprite> _renderer;
};

