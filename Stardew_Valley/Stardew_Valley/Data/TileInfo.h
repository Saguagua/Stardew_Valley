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

	TileInfo(int bitFlag)
		:_bitFlag(bitFlag) {}
	~TileInfo() {}

	int GetBitFlag() { return _bitFlag; }
	void SetBitFlag(int bitFlag) { _bitFlag = bitFlag; }
private:
	int _bitFlag = 0;
};