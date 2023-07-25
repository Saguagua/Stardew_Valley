#include "framework.h"
#include "EatableItem.h"
#include "../../Data/PlayerInfo.h"

EatableItem::EatableItem(int itemCode, short count)
	:GameObject(itemCode, count)
{
}

int EatableItem::UseItem()
{
	PLAYER->AddMaxHP(_maxHpCost);
	PLAYER->AddHP(_hpCost);
	PLAYER->AddMaxStamina(_maxStaminaCost);
	PLAYER->AddStamina(_staminaCost);

	return 0;
}
