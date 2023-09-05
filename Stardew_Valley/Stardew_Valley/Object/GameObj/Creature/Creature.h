#pragma once
#define FRONT 0
#define SIDE 1
#define BACK 2

class Creature
{
public:
	Creature(string name, Vector2 size);
	virtual ~Creature() {}

	virtual void Update();
	virtual void Render();

	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
	Vector2 GetWorldPos() { return _col->GetWorldPos(); }

	virtual void AddHP(short cost);

	short GetMaxHp() { return _maxHp; }
	short GetHp() { return _hp; }
	int GetDirection() { return _dir; }
	bool IsFreeze() { return _freeze; }
	void SetActive(bool val) { _isActive = val; }
	void StartUntouchable() { _untouchable = 1.0f; }

	bool IsUntouchable() { return _untouchable > 0.0f; }
protected:
	virtual void CreateAction() abstract;
	virtual void SetAction(int index);
	virtual void SetPause(bool val);
	void SetDirection(Vector2 pos);

	shared_ptr<RectCollider> _col;

	shared_ptr<Transform> _bodySlot;

	shared_ptr<LightTextureRect> _body;

	vector<shared_ptr<Action>> _actions;

	string _name;
	short _maxHp;
	short _hp;
	Vector2 _size;


	float _untouchable = 0;
	int _state = 0;
	int _actionIndex = 0;
	int _dir = FRONT;
	bool _isActive = false;
	bool _freeze = false;
};

