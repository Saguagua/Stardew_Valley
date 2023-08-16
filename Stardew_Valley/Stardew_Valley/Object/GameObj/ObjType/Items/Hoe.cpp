#include "framework.h"
#include "../../../Tile/TileType/ArableTile.h"
#include "../../../../Data/TileInfo.h"
#include "../../../Tile/Tile.h"
#include "Item.h"
#include "Hoe.h"


void Hoe::KeyInput()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
	}
	else if (KEY_PRESS(VK_LBUTTON))
	{
		_chargeTime += DELTA_TIME;
		if (_chargeTime > 1)
		{
			_chargeTime = 0;
			if (_chargeCount < 2)
				_chargeCount++;
		}
	}
	else if (KEY_UP(VK_LBUTTON))
	{
		DATA->AddStamina(_cost);
		auto tiles = TileMap::GetInstance()->GetFocusedBlocks(_chargeCount);

		for (auto tile : tiles)
		{
			if (DATA->GetTileInfo(tile->GetName())->GetBitFlag() & TileInfo::Type::FARMING)
			{
				dynamic_pointer_cast<ArableTile>(tile)->SetDritName("HoeDirt");
				dynamic_pointer_cast<ArableTile>(tile)->SetPlantable(true);
			}

		}
	}
}
