#include "framework.h"
#include "BreakableItem.h"

BreakableItem::BreakableItem(int itemCode, short count, short hp)
	:GameObject(itemCode, count), _hp(hp)
{
}

void BreakableItem::GetDamage(int amount)
{
	if (_hp <= amount)
	{
		ObjectSpawner::GetInstance()->ActiveDropItem(_pos, _dropItemCode, _dropItemCount);
	}
}

void BreakableItem::Interaction()
{
}
