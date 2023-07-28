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
		WEAPON,
		SEED,
		FARMMING,
		BLANK
	};

	ObjectInfo(string name, vector<short> vals)
		:_name(name), _vals(vals) {}
	~ObjectInfo() {}

	string GetName() { return _name; }
	vector<short>& GetVals() { return _vals; }

private:
	string _name;
	vector<short> _vals;
};