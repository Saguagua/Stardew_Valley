#pragma once
#include "../Tile.h"
class ArableTile : public Tile
{
public:
	ArableTile(string name, Vector2 pos, string cropName, int progress, int quality)
		:Tile(name, pos, cropName) 
	{
		//ObjectSpawner::GetInstance()->CreateCrop(cropName, progress, quality);
	}

	virtual ~ArableTile() {}

	virtual void Interaction() override;

private:
	weak_ptr<class Crop> _crop;
};

