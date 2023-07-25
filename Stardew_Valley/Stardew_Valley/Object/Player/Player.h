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

public:
	Player();
	~Player() {}

	void Update();
	void Render();

	void SetDebug(bool val) { _collider->SetDebug(val); }

	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }
	shared_ptr<CircleCollider> GetCollider() { return _collider; }
	Vector2 GetWorldPos();
private:
	void SetInfos();
	void CreateAction();
	void SetAction(PlayerAction state);

	void KeyInput();
	void Move();
	void Items();
	void Mouse();

	shared_ptr<CircleCollider> _collider;
	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _itemSlot;
	shared_ptr<TextureRect> _body;
	shared_ptr<TextureRect> _arm;
	shared_ptr<TextureRect> _obj;

	int _itemIndex;
	vector<shared_ptr<GameObject>> _items;
	short _maxHp;
	short _hp;
	short _maxStamina;
	short _stamina;

	vector<shared_ptr<Action>> _bodyActions;
	vector<shared_ptr<Action>> _armActions;

	PlayerAction _bodyIndex = PlayerAction::FRONTIDLE;
	PlayerAction _armIndex = PlayerAction::FRONTIDLE;
	int _selectedItemIndex = 0;
};

