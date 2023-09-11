#pragma once

class Player :public Creature
{
public:
	enum PlayerAction
	{
		IDLE = 0,
		RUN = 3,
		TOOL = 6,
		TOOL2 = 9,
		FISHING1 = 12,
		FISHING2 = 15,
		FISHING3 = 18,
		ATTACK = 21,
		HOLD = 24
	};

	Player();
	~Player() {}
	
	virtual void Update() override;
	virtual void Render() override;

	shared_ptr<CircleCollider> GetMagnatic() { return _magnatic; }
	vector<CallBackInt> GetCurIndexCallback();

	short GetMaxStamina() { return _maxStamina; }
	short GetStamina() { return _stamina; }
	int GetCurIndex() { return _curIndex; }
	vector<shared_ptr<Item>>& GetItems() { return _items; }
	shared_ptr<Item> GetItem(int index) { return _items[index]; }

	shared_ptr<RectCollider> _interactCol;
protected:
	void GetDatas();
	void SetFreeze(bool val) { _freeze = val; }
	//Actions
	virtual void CreateAction() override;
	void SetArmAction(int index);
	void SetIdle();
	void SetNextAction(int index);

	//Inputs
	void Move();

	//Colliders
	shared_ptr<CircleCollider> _magnatic;
	//Slots
	shared_ptr<Transform> _itemSlot;

	//Action
	vector<shared_ptr<Action>> _armActions;

	//Renderers
	shared_ptr<LightTextureRect> _arm;
	shared_ptr<Sprite> _obj;

	short _maxStamina;
	short _stamina;
	vector<shared_ptr<Item>> _items;

	int _curIndex = 0;
	int _armIndex = PlayerAction::IDLE;
};