#include "framework.h"
#include "../Items/PickAxe.h"
#include "SpawnInfo.h"
#include "DeployableObject.h"
#include "BreakableItem.h"

void BreakableItem::Interaction()
{
	shared_ptr<Item> item = DATA->GetSelectedItem();
}

void BreakableItem::Spawn(string name, shared_ptr<SpawnInfo> info)
{
	_isActive = true;
	_name = name;
}
