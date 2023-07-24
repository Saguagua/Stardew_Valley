#include "framework.h"
#include "PlayerInfoManager.h"
#include "../../Data/PlayerInfo.h"

PlayerInfoManager* PlayerInfoManager::_instance = nullptr;

PlayerInfoManager::PlayerInfoManager()
{
	GetPlayerInfo();
}

void PlayerInfoManager::GetPlayerInfo()
{
	_info = DATA->GetPlayerInfo();
}
