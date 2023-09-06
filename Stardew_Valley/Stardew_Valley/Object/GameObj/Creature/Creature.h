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

	void AddPos(Vector2 pos) { _col->AddPos(pos); }

	virtual void AddHP(short cost);

	short GetMaxHp() { return _maxHp; }
	short GetHp() { return _hp; }
	int GetDirection() { return _direction; }

	bool IsActive() { return _isActive; }
	bool IsFreeze() { return _freeze; }
	void SetActive(bool val) { _isActive = val; }
	void StartUntouchable() { _untouchable = 1.0f; }
	bool IsUntouchable() { return _untouchable > 0; }
	void SetDirection(Vector2 pos);
protected:
	virtual void CreateAction() abstract;
	virtual void SetAction(int index);
	virtual void SetPause(bool val);

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
	int _direction = FRONT;
	bool _isActive = false;
	bool _freeze = false;

	float _counter = 0.0f;
};

