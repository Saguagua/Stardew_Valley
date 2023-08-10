#pragma once
#include "framework.h"

class ObjectInfo
{
public:
	struct Position
	{
		int x;
		int y;
		int w;
		int h;
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

	ObjectInfo(string name)
		:_name(name) {}
	~ObjectInfo() {}

	string GetName() { return _name; }
	vector<int>& GetVals() { return _vals; }

	void SetVals(vector<int> vals) { _vals = vals; }
	void AddPosition(Position pos) { _positions.push_back(pos); }

private:
	string _name;
	vector<int> _vals;
	vector<Position> _positions;
};