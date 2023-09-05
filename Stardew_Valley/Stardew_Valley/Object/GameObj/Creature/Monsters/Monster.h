#pragma once
class Monster :public Creature
{
	enum MonsterAction
	{
		IDLE,
		MOVE,
		DEATH
	};
public:
	Monster(string name, Vector2 size);
	virtual ~Monster() {}

	void Move(Vector2 direction);

	virtual void Render();
	virtual void Update();


	shared_ptr<CircleCollider> GetDetectArea() { return _detectArea; }
protected:
	shared_ptr<CircleCollider> _detectArea;

	Vector2 _direction;
	float _stopTimer = 5.0f;
	float _moveTimer = 1.0f;
	float _speed = 100.0f;
};

