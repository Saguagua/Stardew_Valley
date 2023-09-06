#pragma once
class Monster :public Creature
{
	
public:
	Monster(string name, Vector2 size, float areaSize);
	virtual ~Monster() {}

	void Move(Vector2 direction);

	virtual void Render();
	virtual void Update();

	shared_ptr<CircleCollider> GetDetectArea() { return _detectArea; }
	void SetIdle();
protected:
	enum MonsterAction
	{
		IDLE,
		MOVE,
		DEATH
	};


	shared_ptr<CircleCollider> _detectArea;

	Vector2 _forceDirection;
};

