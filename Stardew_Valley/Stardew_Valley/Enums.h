#pragma once

enum TileType
{
	NONE,
	BLOCK = (1 << 0),
	FARMING = (1 << 1),
	FISHING = (1 << 2)
};

enum PlayerState
{
	IDLE = 0,
	RUN = 15,
	RUNF = (1 << 0),
	RUNB = (1 << 1),
	RUNL = (1 << 2),
	RUNR = (1 << 3),
	ACTION = (1 << 4),
	HOLDING = (1 << 5),
	IMMOVEABLE = (1 << 6),
	DEAD = (1 << 7)
};

enum SpriteType
{
	OBJECT,
	UI
};
