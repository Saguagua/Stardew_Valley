#pragma once
#include "../../framework.h"

struct TileInfo
{
	TileInfo(Vector2 centerPos, Vector2 curFrame)
	{
		this->centerPos = centerPos;
		this->curFrame = curFrame;
	}

	Vector2 centerPos = { 0,0 };
	Vector2 curFrame = { 0,0 };
};