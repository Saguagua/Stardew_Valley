#pragma once


class Player :public Creature
{
protected:
	enum PlayerAction
	{
		IDLE = 0,
		RUN = 3,
		TOOL = 6,
		//WATER,
		HOLD = 9,
	};

public:
	Player();
	~Player() {}
	
	virtual void Update() override;
	virtual void Render() override;

	shared_ptr<CircleCollider> GetMagnatic() { return _magnatic; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
	Vector2 GetWorldPos() { return _col->GetWorldPos(); }
	vector<CallBackInt> GetCurIndexCallback();

	short GetMaxHp() { return _maxHp; }
	short GetMaxStamina() { return _maxStamina; }
	short GetHp() { return _hp; }
	short GetStamina() { return _stamina; }
	int GetCurIndex() { return _curIndex; }
	vector<shared_ptr<Item>>& GetItems() { return _items; }

protected:
	void GetDatas();

	//Actions
	virtual void CreateAction() override;
	void SetArmAction(int index);
	
	//Inputs
	void Move();

	//Colliders
	shared_ptr<CircleCollider> _magnatic;

	//Slots
	shared_ptr<Transform> _itemSlot;

	//Action
	vector<shared_ptr<Action>> _armActions;

	//Renderers
	shared_ptr<LightTextureRect> _body;
	shared_ptr<LightTextureRect> _arm;
	shared_ptr<Sprite> _obj;

	short _maxStamina;
	short _stamina;
	vector<shared_ptr<Item>> _items;


	int _curIndex = 0;
	int _armIndex = PlayerAction::IDLE;

};