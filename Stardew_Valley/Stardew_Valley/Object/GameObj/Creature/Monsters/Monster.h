#pragma once
class Monster :public Creature
{
public:
	enum MoveType
	{
		FLYING,
		WALK
	};
	Monster(string name, Vector2 size, float areaSize, MoveType type);
	virtual ~Monster() {}

	virtual void Render();
	virtual void Update();

	virtual void Detect(shared_ptr<PlayerFight> player) abstract;

	void AddHP(short cost);
	shared_ptr<CircleCollider> GetDetectArea() { return _detectArea; }
	void SetIdle();
	void Spawn(Vector2 pos);

	MoveType _type;
protected:
	enum MonsterAction
	{
		IDLE,
		MOVE,
		DEATH
	};

	virtual void Initialize() abstract;
	shared_ptr<CircleCollider> _detectArea;

	Vector2 _forceDirection;
};

