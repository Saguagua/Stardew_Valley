#pragma once

class Player :public Creature
{
public:
	enum PlayerAction
	{
		IDLE = 0,
		RUN = 3,
		ATTACK = 6,
		TOOL = 9,
		TOOL2 = 12,
		FISHING1 = 15,
		FISHING2 = 18,
		FISHING3 = 21,
		EAT = 24,
		DEATH = 27,
		HOLD = 30
	};

	Player();
	~Player() {}
	
	virtual void Update() override;
	virtual void Render() override;
	void PostRender();

	shared_ptr<CircleCollider> GetMagnatic() { return _magnatic; }
	vector<CallBackInt> GetCurIndexCallback();

	bool IsDead() { return _state & PlayerState::DEAD; }

	short GetMaxStamina() { return _maxStamina; }
	short GetStamina() { return _stamina; }
	int GetCurIndex() { return _curIndex; }
	vector<shared_ptr<Item>>& GetItems() { return _items; }
	shared_ptr<Item> GetCurItem() { return _items[_curIndex]; }
	shared_ptr<Item> GetItem(int index) { return _items[index]; }

	shared_ptr<RectCollider> _interactCol;
	void SetIdle();
protected:
	void GetDatas();

	void SetFreeze(bool val) { _freeze = val; }

	//Actions
	virtual void CreateAction() override;
	void SetArmAction(int index);
	void SetNextAction(int index);


	//Inputs
	void Move();

	//Colliders
	shared_ptr<CircleCollider> _magnatic;

	//Action
	vector<shared_ptr<Action>> _armActions;

	//Renderers
	shared_ptr<LightTextureRect> _arm;

	short _maxStamina;
	short _stamina;
	vector<shared_ptr<Item>> _items;

	int _curIndex = 0;
	int _armIndex = PlayerAction::IDLE;

};