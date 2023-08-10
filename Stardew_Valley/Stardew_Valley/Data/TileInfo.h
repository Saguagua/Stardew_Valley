#pragma once
#include "framework.h"

class TileInfo
{
public:
	enum Type
	{
		NONE,
		BLOCK = (1 << 0),
		FARMING = (1 << 1),
		FISHING = (1 << 2)
	};

	struct Position
	{
		int x;
		int y;
		int w;
		int h;
	};

	TileInfo(string name)
		:_name(name) {}
	~TileInfo() {}

	int GetBitFlag() { return _bitFlag; }
	vector<Position>& GetPoses() { return _positions; }
	void SetBitFlag(int bitFlag) { _bitFlag = bitFlag; }
	void AddPosition(Position pos) { _positions.push_back(pos); }
private:
	string _name;
	int _bitFlag = 0;
	vector<Position> _positions; //xml 위치임 명칭 수정 필요
};