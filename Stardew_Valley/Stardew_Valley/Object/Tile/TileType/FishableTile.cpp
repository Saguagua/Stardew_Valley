#include "framework.h"
#include "../Tile.h"
#include "../../GameObj/ObjType/FishingRod.h"
#include "FishableTile.h"

void FishableTile::Interaction()
{
	shared_ptr<GameObject> obj = DATA->GetSelectedItem();

	if (obj->GetType() == ObjectInfo::Type::FISHINGROD)
		dynamic_pointer_cast<FishingRod>(obj)->Interaction();
}
