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
		STAMINA
	};

	PlayerSubscribe(shared_ptr<PlayerImproved> player, Type type) 
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
	int _type = ALL;
};