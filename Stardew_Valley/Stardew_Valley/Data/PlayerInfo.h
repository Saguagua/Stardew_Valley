#pragma once
#include "../Object/GameObj/ObjType/Items/Item.h"
#include "framework.h"

class PlayerInfo
{
public:
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

	PlayerInfo(string name, short maxHp, short hp, short maxStamina, short stamina, vector<shared_ptr<class Item>> items)
		:_name(name), _maxHp(maxHp), _hp(hp), _maxStamina(maxStamina), _stamina(stamina), _items(items)
	{
		_collider = make_shared<CircleCollider>(15);
	}
	~PlayerInfo() {}

	string GetName() { return _name; }
	short GetHP() { return _hp; }
	short GetMaxHP() { return _maxHp; }
	short GetStamina() { return _stamina; }
	short GetMaxStamina() { return _maxStamina; }
	vector<shared_ptr<Item>>& GetItems() { return _items; }
	shared_ptr<Item> GetItem(int index) { return _items[index]; }
	shared_ptr<CircleCollider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }
	Vector2 GetWorldPos() { return _collider->GetWorldPos(); }
	int GetState() { return _playerState; }
	int& GetStateRef() { return _playerState; }
	int GetSelectedIndex() { return _selectedIndex; }

	void SetHP(short amount) { _hp = amount; }
	void SetMaxHP(short amount) { _maxHp = amount; }
	void SetStamina(short amount) { _stamina = amount; }
	void SetMaxStamina(short amount) { _maxStamina = amount; }
	void SetPos(Vector2 pos) { _collider->SetPos(pos); }
	void SetScale(Vector2 scale) { _collider->SetScale(scale); }
	void SetState(int state) { _playerState = state; }
	void SetSelectedIndex(int index) { _selectedIndex = index; }

	void AddHP(short amount) { _hp += amount; }
	void AddMaxHP(short amount) { _maxHp += amount; }
	void AddStamina(short amount) { _stamina += amount; }
	void AddMaxStamina(short amount) { _maxStamina += amount; }

private:
	string _name;
	short _maxHp;
	short _hp;
	short _maxStamina;
	short _stamina;
	vector<shared_ptr<Item>> _items;
	shared_ptr<CircleCollider> _collider;

	int _playerState = PlayerState::IDLE;
	int _selectedIndex = 0;
};