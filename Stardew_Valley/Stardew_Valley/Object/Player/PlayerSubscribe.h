#pragma once
#include "framework.h"

struct PlayerSubscribe
{
	enum Type
	{
		ALL,
		ITEMS,
		ENERGY
	};

	PlayerSubscribe(Type type) { _type = type; }

	virtual void UpdateInfo() abstract;
	virtual void Dead() abstract;

	int _type = ALL;
	weak_ptr<PlayerInfo> _playerInfo;
};