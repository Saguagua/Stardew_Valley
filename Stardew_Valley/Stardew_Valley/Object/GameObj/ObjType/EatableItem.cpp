#include "framework.h"
#include "EatableItem.h"

void EatableItem::KeyInput()
{
	DATA->AddMaxHP(_maxHpCost);
	DATA->AddHP(_hpCost);
	DATA->AddMaxStamina(_maxStaminaCost);
	DATA->AddStamina(_staminaCost);
}