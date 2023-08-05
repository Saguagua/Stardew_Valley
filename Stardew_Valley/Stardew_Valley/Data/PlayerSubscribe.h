#pragma once
#include "framework.h"
#include "DataManager.h"
#include "PlayerInfo.h"

struct PlayerSubscribe
{
	enum Type
	{
		ALL,
		ITEMS
	};

	PlayerSubscribe()
	{
		_playerInfo = DATA->RequestPlayerSubScribe(this);
	}

	virtual void UpdateInfo() abstract;
	virtual void Dead() abstract;

	weak_ptr<PlayerInfo> _playerInfo;
	int _type = ALL;
};