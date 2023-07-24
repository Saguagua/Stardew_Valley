#include "framework.h"
#include "BreakableItem.h"

BreakableItem::BreakableItem(int itemCode)
	:GameObject(itemCode)
{
}

void BreakableItem::CreateAction()
{
}

void BreakableItem::GetDamage(int amount)
{
	if (_hp <= amount)
	{

	}
}

int BreakableItem::UseItem()
{
	return 0;
}
