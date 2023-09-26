#pragma once
#include "framework.h"
#include "PlayerImproved.h"

struct PlayerSubscribe
{
	enum Type
	{
		ALL,
		ITEMS,
		HP,
		STAMINA,
		MONEY
	};

	PlayerSubscribe(shared_ptr<PlayerImproved> player, PlayerSubscribe::Type type) 
	{
		_player = player;
		_type = type;
		_player.lock()->RequestSubscribe(this);
	}
	virtual ~PlayerSubscribe() {}

	void SetType(Type type) { _type = type; }
	virtual void UpdateInfo() abstract;
	virtual void Dead() abstract;

	weak_ptr<PlayerImproved> _player;
	Type _type = ALL;
};