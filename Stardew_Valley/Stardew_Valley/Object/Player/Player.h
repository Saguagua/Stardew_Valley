#pragma once

class PlayerSubscribe;
#define FRONT 0
#define SIDE 1
#define BACK 2

class Player
{
	friend class Item;
	friend class BagUI;
	friend class ItemSlot;

	Player();
	~Player() {}

	enum PlayerAction
	{
		IDLE = 0,
		RUN = 3,
		TOOL = 6,
		//WATER,
		HOLD = 9,
	};

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Player();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Player* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void Update();
	void Render();
	
	shared_ptr<PlayerInfo> RequestSubscribe(PlayerSubscribe* subscriber);
	void CancelSubscribe(PlayerSubscribe* subscriber);

	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<CircleCollider> GetMagnatic() { return _magnatic; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
	Vector2 GetWorldPos() { return _col->GetWorldPos(); }
	vector<CallBackInt> GetSelectedIndexCallback();

	const shared_ptr<Item> GetSelectedItem() { return _playerInfo->GetSelectedItem(); }

	bool AddMaxHP(short cost);
	bool AddMaxStamina(short cost);
	bool AddHP(short cost);
	bool AddStamina(short cost);
	bool AddItem(string name);

private:
	static Player* _instance;

	void CreateAction();
	void SetBodyAction(int index);
	void SetArmAction(int index);
	void SetPause(bool val);
	

	void KeyInput();
	void Move();
	void Mouse();
	void Items();

	void SetSelectedItemIndex(int index);
	
	void SetDirection(Vector2 pos);
	void SwapItems(int index1, int index2);

	void SendToSubscribers(int type);

	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _itemSlot;

	vector<shared_ptr<Action>> _bodyActions;
	vector<shared_ptr<Action>> _armActions;

	shared_ptr<RectCollider> _col;
	shared_ptr<CircleCollider> _magnatic;

	shared_ptr<LightTextureRect> _body;
	shared_ptr<LightTextureRect> _arm;
	shared_ptr<Sprite> _obj;

	shared_ptr<PlayerInfo> _playerInfo = DATA->GetPlayerInfo();
	list<PlayerSubscribe*> _subscribers;

	int _bodyIndex = PlayerAction::IDLE;
	int _armIndex = PlayerAction::IDLE;

	int _dir = FRONT;

	bool _froze = false;
};