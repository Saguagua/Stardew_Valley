#pragma once
#include "framework.h"

class ObjectInfo
{
public:
	enum Type
	{
		NONE,
		BREAKABLE,
		PICKABLE,
		EATABLE,
		DROP,
		AXE,
		PICKAXE,
		HOE,
		WATERINGCAN,
		FISHINGROD,
		WEAPON
	};

	ObjectInfo(string name, vector<int> vals)
		:_name(name), _vals(vals) {}
	~ObjectInfo() {}

	string GetName() { return _name; }
	vector<int>& GetVals() { return _vals; }

private:
	string _name;
	vector<int> _vals;
};