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

	TileInfo(int bitFlag)
		:_bitFlag(bitFlag) {}
	~TileInfo() {}

	int GetBitFlag() { return _bitFlag; }

	void SetBitFlag(int bitFlag) { _bitFlag = bitFlag; }
	void AddPosition(Position pos) { _positions.push_back(pos); }
private:
	int _bitFlag = 0;
	vector<Position> _positions;
};