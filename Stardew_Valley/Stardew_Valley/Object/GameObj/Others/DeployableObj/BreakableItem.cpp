#include "framework.h"
#include "DeployableObject.h"
#include "BreakableItem.h"



vector<int> BreakableItem::GetProperty()
{
	return vector<int>(2, (_hp, 0));
}

void BreakableItem::GetDamage(shared_ptr<Item> item)
{
	if (!_isActive)
		return;
	if (item->GetType() == _breakType)
	{
		_hp -= item->GetVals()[2];

		if (_hp <= 0)
		{
			OBJECT_SPAWNER->ActiveDropItem(_name, _centerPos);
			DungeonSystem::GetInstance()->SpawnDoor(_centerPos);
			_name = "BLANK";
			_isActive = false;
		}
	}
}


