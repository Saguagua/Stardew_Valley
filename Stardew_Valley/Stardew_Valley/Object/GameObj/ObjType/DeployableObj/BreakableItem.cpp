#include "framework.h"
#include "../Items/PickAxe.h"
#include "SpawnInfo.h"
#include "DeployableObject.h"
#include "BreakableItem.h"

void BreakableItem::Interaction()
{
	//shared_ptr<PickAxe> item = DATA->GetSelectedItem();
	//if ()
}

void BreakableItem::Spawn(string name, shared_ptr<SpawnInfo> info)
{
	_isActive = true;
	_name = name;
}
