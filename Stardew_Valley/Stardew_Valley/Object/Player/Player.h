#pragma once
class Player
{
	enum class PlayerState
	{
		FRONT,
		SIDE,
		BACK,
		DAMAGED
	};

public:
	Player();
	~Player() {}

	void Update();
	void Render();

	void KeyInput();

	void SetDebug(bool val) { _collider->SetDebug(val); }
	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }
	shared_ptr<CircleCollider> GetCollider() { return _collider; }
	Vector2 GetWorldPos();
private:
	void CreateAction();

	vector<shared_ptr<Action>> _bodyActions;
	vector<shared_ptr<Action>> _armActions;

	shared_ptr<Transform> _bodySlot;
	shared_ptr<CircleCollider> _collider;
	shared_ptr<TextureRect> _body;
	shared_ptr<TextureRect> _arm;

	int _bodyIndex = 0;
	int _armIndex = 0;
	int _selectedItemIndex = 0;
};

