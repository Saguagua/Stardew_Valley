#pragma once
#include "framework.h"

class ObjectInfo
{
public:
	struct Position
	{
		int x;
		int y;
		int width;
		int height;
	};
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

	ObjectInfo(string name, vector<int> vals)
		:_name(name), _vals(vals) {}
	~ObjectInfo() {}

	string GetName() { return _name; }
	vector<int>& GetVals() { return _vals; }

	void AddPosition(Position pos) { _positions.push_back(pos); }

private:
	string _name;
	vector<int> _vals;
	vector<Position> _positions;
};