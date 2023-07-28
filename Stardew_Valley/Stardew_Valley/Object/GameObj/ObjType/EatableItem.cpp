#include "framework.h"
#include "EatableItem.h"

void EatableItem::Interaction()
{
	PLAYER->AddMaxHP(_maxHpCost);
	PLAYER->AddHP(_hpCost);
	PLAYER->AddMaxStamina(_maxStaminaCost);
	PLAYER->AddStamina(_staminaCost);
}