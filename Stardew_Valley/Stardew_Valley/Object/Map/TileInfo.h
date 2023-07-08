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

	TileInfo(Vector2 centerPos, Vector2 curClip, TileInfo::Type type)
	{
		this->centerPos = centerPos;
		this->curClip = curClip;
		this->type = type;
	}

	Vector2 centerPos = { 0,0 };
	Vector2 curClip = { 0,0 };
	TileInfo::Type type = TileInfo::Type::NONE;
	XMFLOAT4 color = GREEN;
};