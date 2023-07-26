#include "framework.h"
#include "EatableItem.h"

EatableItem::EatableItem(int itemCode, short count)
	:GameObject(itemCode, count)
{
}

void EatableItem::Interaction()
{
	PLAYER->AddMaxHP(_maxHpCost);
	PLAYER->AddHP(_hpCost);
	PLAYER->AddMaxStamina(_maxStaminaCost);
	PLAYER->AddStamina(_staminaCost);
}