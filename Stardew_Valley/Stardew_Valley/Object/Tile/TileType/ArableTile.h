#pragma once
#include "../Tile.h"
class ArableTile : public Tile
{
public:
	ArableTile(Vector2 pos, int tileCode, int objCode)
		:Tile(pos, tileCode, objCode) {}
	virtual ~ArableTile() {}

	virtual void Interaction() override;
};

