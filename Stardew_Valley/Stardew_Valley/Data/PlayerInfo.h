#pragma once
#include "framework.h"

class PlayerInfo
{
public:
	PlayerInfo(string name, short maxHp, short hp, short maxStamina, short stamina, vector<shared_ptr<GameObject>>& items, Vector2 pos)
		:_name(name), _maxHp(maxHp), _hp(hp), _maxStamina(maxStamina), _stamina(stamina), _items(items), _pos(pos)
	{}
	PlayerInfo() {}
	~PlayerInfo() {}

	string GetName() { return _name; }
	short GetHP() { return _hp; }
	short GetMaxHP() { return _maxHp; }
	short GetStamina() { return _stamina; }
	short GetMaxStamina() { return _maxStamina; }
	vector<shared_ptr<GameObject>> GetItems() { return _items; }
	shared_ptr<GameObject> GetItem(int index) { return _items[index]; }
	Vector2 GetPos() { return _pos; }

	void SetHP(short amount) { _hp = amount; }
	void SetMaxHP(short amount) { _maxHp = amount; }
	void SetStamina(short amount) { _stamina = amount; }
	void SetMaxStamina(short amount) { _maxStamina = amount; }
	void SetPos(Vector2 pos) { _pos = pos; }

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
	vector<shared_ptr<GameObject>> _items;
	Vector2 _pos;
};