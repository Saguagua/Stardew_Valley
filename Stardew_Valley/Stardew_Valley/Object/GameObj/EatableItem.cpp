#include "framework.h"
#include "EatableItem.h"
#include "../Player/PlayerInfoManager.h"
#include "../../Data/PlayerInfo.h"

EatableItem::EatableItem(int itemCode, short count)
	:GameObject(itemCode, count)
{
}

int EatableItem::UseItem()
{
	PLAYER->GetInfo()->AddMaxHP(_maxHpCost);
	PLAYER->GetInfo()->AddHP(_hpCost);
	PLAYER->GetInfo()->AddMaxStamina(_maxStaminaCost);
	PLAYER->GetInfo()->AddStamina(_staminaCost);

	return 0;
}

void EatableItem::GetHP()
{
}
