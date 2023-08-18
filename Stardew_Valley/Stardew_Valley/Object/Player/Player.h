#pragma once
class Player
{
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

		return _instance;
	}

	void Update();
	void Render();
	
	void SetSelectedItemIndex(int index);

	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
	shared_ptr<PlayerInfo> GetPlayerInfo() { return _playerInfo; }
	Vector2 GetWorldPos() { return _col->GetWorldPos(); }

private:
	static Player* _instance;

	void CreateAction();
	void SetAction(int index);
	void SetRun(int index);

	void KeyInput();
	void Move();
	void Items();
	void Mouse();

	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _itemSlot;

	vector<shared_ptr<Action>> _bodyActions;
	vector<shared_ptr<Action>> _armActions;

	shared_ptr<RectCollider> _col;

	shared_ptr<LightTextureRect> _body;
	shared_ptr<LightTextureRect> _arm;
	shared_ptr<Sprite> _obj;

	shared_ptr<PlayerInfo> _playerInfo = DATA->GetPlayerInfo();
	vector<PlayerSubscribe*> _playerSubscribers;

	int _bodyIndex = PlayerAction::FRONTIDLE;
	int _armIndex = PlayerAction::FRONTIDLE;
};