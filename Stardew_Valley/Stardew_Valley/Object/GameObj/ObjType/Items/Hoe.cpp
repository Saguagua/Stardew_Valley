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
		DATA->AddStamina(_cost);

		weak_ptr<Tile> tile = TileMap::GetInstance()->GetMouseToPlayerIndex();

		if (DATA->GetTileInfo(tile.lock()->GetName())->GetBitFlag() & TileInfo::Type::FARMING)
		{
			tile.lock()->Interaction();

		}
	}
}
