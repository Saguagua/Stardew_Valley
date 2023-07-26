#include "framework.h"
#include "../../../Data/ObjectInfo.h"
#include "BreakableItem.h"
#include "../../Tile/Tile.h"
#include "PickAxe.h"

void PickAxe::UseItem()
{
	shared_ptr<Tile> info = TILEMAP->GetMouseToPlayerIndex(W_MOUSE_POS);
	shared_ptr<GameObject> obj = info->GetObj();

	if (obj->GetType() == ObjectInfo::Type::BREAKABLE)
	{
		dynamic_pointer_cast<BreakableItem>(obj)->GetDamage(_damage);
	}

	PLAYER->AddStamina(_cost);
}
