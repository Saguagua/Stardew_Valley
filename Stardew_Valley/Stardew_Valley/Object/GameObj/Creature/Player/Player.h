#pragma once


class Player :public Creature
{
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
	
	void Update();
	void Render();
	
	shared_ptr<PlayerInfo> RequestSubscribe(PlayerSubscribe* subscriber);
	void CancelSubscribe(PlayerSubscribe* subscriber);

	shared_ptr<CircleCollider> GetMagnatic() { return _magnatic; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
	Vector2 GetWorldPos() { return _col->GetWorldPos(); }
	vector<CallBackInt> GetSelectedIndexCallback();

	bool AddMaxHP(short cost);
	bool AddMaxStamina(short cost);
	bool AddStamina(short cost);
	bool AddItem(string name);

protected:
	//Actions
	virtual void CreateAction() override;
	virtual void SetAction(int index) override;
	void SetArmAction(int index);
	
	//Inputs
	void Move();
	void Mouse();
	void Items();;

	//Misc
	void SetSelectedItemIndex(int index);
	void SwapItems(int index1, int index2);

	//Send
	void SendToSubscribers(int type);

	//Colliders
	shared_ptr<RectCollider> _col;
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