#pragma once
class Player
{
	enum PlayerAction
	{
		FRONTIDLE,
		SIDEIDLE,
		BACKIDLE,
		FRONTRUN,
		SIDERUN,
		BACKRUN,
		FRONTHOLD,
		SIDEHOLD,
		BACKHOLD
	};

	enum PlayerState
	{
		IDLE = 0,
		RUN = (15 < 4),
		RUNF = (1 << 0),
		RUNB = (1 << 1),
		RUNL = (1 << 2),
		RUNR = (1 << 3),
		ACTION = (1 << 4),
		HOLDING = (1 << 5),
		DEAD = (1 << 6)
	};

	Player();
	~Player() {}

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

	void SetDebug(bool val) { _col->SetDebug(val); }
	void SetPos(Vector2 pos) { _col->SetPos(pos); }
	void SetAngle(float angle) { _col->SetAngle(angle); }
	void SetScale(Vector2 scale) { _col->SetScale(scale); }
	void SetSelectedItemIndex(int index);

	void AddPos(Vector2 pos) { _col->AddPos(pos); }
	void AddAngle(float angle) { _col->AddAngle(angle); }
	void AddScale(Vector2 scale) { _col->AddScale(scale); }
	void AddMaxHP(short amount);
	void AddMaxStamina(short amount);
	bool AddHP(short amount);
	bool AddStamina(short amount);


	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
	shared_ptr<CircleCollider> GetCollider() { return _col; }
	shared_ptr<class GameObject> GetSelectedItem();
	vector<shared_ptr<GameObject>> GetItems();
	shared_ptr<class PlayerInfo> GetPlayerInfo() { return _playerInfo; }
	vector<CallBackInt> GetSelectedIndexCallback();
	Vector2 GetWorldPos();
	bool GetItem(int objCode);

private:
	void SetInfos()
	{
		_playerInfo = DATA->GetPlayerInfo();
	}

	void CreateAction();
	void SetAction(int index);
	void SetRun(int index);

	void KeyInput();
	void Move();
	void Items();

	static Player* _instance;
	shared_ptr<class PlayerInfo> _playerInfo;

	shared_ptr<CircleCollider> _col;
	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _itemSlot;
	shared_ptr<TextureRect> _body;
	shared_ptr<TextureRect> _arm;
	shared_ptr<TextureRect> _obj;

	vector<shared_ptr<Action>> _bodyActions;
	vector<shared_ptr<Action>> _armActions;

	int _bodyIndex = PlayerAction::FRONTIDLE;
	int _armIndex = PlayerAction::FRONTIDLE;
	int bodyIn;
	int _selectedItemIndex = 0;
	int _playerState = Player::PlayerState::IDLE;
};

