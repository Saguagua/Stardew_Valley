#pragma once
#include "framework.h"

class PlayerInfo
{
public:
	PlayerInfo(string name, int hp, int stamina, vector<shared_ptr<GameObject>>& items)
		:_name(name), _hp(hp), _stamina(stamina), _items(items)
	{}
	~PlayerInfo() {}

	string GetName() { return _name; }
	int GetHP() { return _hp; }
	int GetStamina() { return _stamina; }
	vector<shared_ptr<GameObject>> GetItems() { return _items; }

private:
	string _name;
	int _hp;
	int _stamina;
	vector<shared_ptr<GameObject>> _items;
};