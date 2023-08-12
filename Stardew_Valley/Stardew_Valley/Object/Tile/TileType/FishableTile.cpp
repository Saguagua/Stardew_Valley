#include "framework.h"
#include "../Tile.h"
#include "../../GameObj/ObjType/Items/FishingRod.h"
#include "FishableTile.h"

void FishableTile::Interaction()
{
	shared_ptr<Item> obj = DATA->GetSelectedItem();

	//if (obj->GetType() == ObjectInfo::Type::FISHINGROD)
	//	obj->KeyInput();
}
