#include "framework.h"
#include "../../../Tile/TileType/ArableTile.h"
#include "../../../Tile/Tile.h"
#include "Item.h"
#include "Hoe.h"


void Hoe::KeyInput()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		
		_chargeCount = 0;
		_chargeTime = 0;
		_point = W_MOUSE_POS;
	}
	else if (KEY_PRESS(VK_LBUTTON))
	{
		_chargeTime += DELTA_TIME;

		if (_chargeTime > 1)
		{
			_chargeTime = 0;
			if (_chargeCount < 2)
				_chargeCount++;

			TileMap::GetInstance()->Hoeing(_point, _chargeCount);
		}
	}
	else if (KEY_UP(VK_LBUTTON))
	{
		//DATA->AddStamina(_cost);

		TileMap::GetInstance()->Hoeing(_point, _chargeCount);
	}
}
