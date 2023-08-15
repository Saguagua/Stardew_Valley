#pragma once
#include "../Tile.h"
class ArableTile : public Tile
{
public:
	ArableTile(string name, Vector2 pos)
		:Tile(name, pos) 
	{
	}

	virtual ~ArableTile() {}

	virtual void Interaction() override;

private:
	weak_ptr<class Crop> _crop;
};

