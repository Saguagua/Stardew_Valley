#pragma once
#include "../../framework.h"

struct TileInfo
{
	enum Type
	{
		NONE,
		MOVEABLE,
		BLOCK,
		SPAWN
	};

	TileInfo(Vector2 centerPos, Vector2 curFrame, TileInfo::Type type)
	{
		this->centerPos = centerPos;
		this->curFrame = curFrame;
		this->type = type;
	}


	Vector2 centerPos = { 0,0 };
	Vector2 curFrame = { 0,0 };
	TileInfo::Type type = TileInfo::Type::NONE;
	XMFLOAT4 color = GREEN;
};