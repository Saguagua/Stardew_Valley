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
		BACKRUN
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

	void AddPos(Vector2 pos) { _col->AddPos(pos); }
	void AddAngle(float angle) { _col->AddAngle(angle); }
	void AddScale(Vector2 scale) { _col->AddScale(scale); }
	void AddMaxHP(short amount);
	void AddMaxStamina(short amount);
	void AddHP(short amount);
	void AddStamina(short amount);

	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
	shared_ptr<CircleCollider> GetCollider() { return _col; }
	Vector2 GetWorldPos();
private:
	void SetInfos()
	{
		_playerInfo = DATA->GetPlayerInfo();
	}

	void CreateAction();
	void SetAction(PlayerAction state);

	void KeyInput();
	void Move();
	void Items();
	void Mouse();

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

	PlayerAction _bodyIndex = PlayerAction::FRONTIDLE;
	PlayerAction _armIndex = PlayerAction::FRONTIDLE;
	int _selectedItemIndex = 0;
};

