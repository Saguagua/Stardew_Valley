#include "framework.h"
#include "PlayerInfoManager.h"
#include "../../Data/PlayerInfo.h"

PlayerInfoManager* PlayerInfoManager::_instance = nullptr;

PlayerInfoManager::PlayerInfoManager()
{
	SetPlayerInfo();
}

void PlayerInfoManager::AddHP(short amount)
{
	_info->AddHP(amount);
}

void PlayerInfoManager::AddMaxHP(short amount)
{
	_info->AddMaxHP(amount);
}

void PlayerInfoManager::AddStamina(short amount)
{
	_info->AddMaxStamina(amount);
}

void PlayerInfoManager::AddMaxStamina(short amount)
{
	_info->AddMaxStamina(amount);
}

void PlayerInfoManager::AddItem(shared_ptr<GameObject> obj)
{
}

void PlayerInfoManager::SetPlayerInfo()
{
	_info = DATA->GetPlayerInfo();
}
