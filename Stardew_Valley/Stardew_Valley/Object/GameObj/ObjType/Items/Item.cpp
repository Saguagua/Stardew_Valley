#include "framework.h"
#include "../../../Tile/TileType/ArableTile.h"
#include "../../../Tile/TileType/FishableTile.h"
#include "../../../Player/Player.h"
#include "Item.h"

void Item::KeyInput()
{
	switch (_type)
	{
	case Item::AXE:
	{
		Axe();
		break;
	}
	case Item::EATABLE:
	{
		Eat();
		break;
	}
	case Item::FISHINGROD:
	{
		Fishing();
		break;
	}
	case Item::HOE:
	{
		Hoe();
		break;
	}
	case Item::PICKAXE:
	{
		PickAxe();
		break;
	}
	case Item::WATERINGCAN:
	{
		Water();
		break;
	}
	case Item::SEED:
	{
		Seed();
		break;
	}
	case Item::FERTILIZER:
	{
		Fertilizer();
		break;
	}
	case Item::WEAPON:
	{
		
		break;
	}
	case Item::FACILITY:
		break;
	default:
		break;
	}
}

void Item::SetItem(string name, short count)
{
	shared_ptr<ItemInfo> info = DATA->GetItemInfos()[name];
	_name = name;
	_count = count;
	_subName = info->GetSubName();
	_price = info->GetPrice();
	_type = info->GetType();
	_vals = info->GetVals();
}

bool Item::AddCount()
{
	return false;
}

void Item::Hoe()
{
	//0 : level
	//1 : cost

	if (KEY_DOWN(VK_LBUTTON))
	{
		_chargeCount = 0;
		_chargeTime = 0;
		_point = W_MOUSE_POS;
	}
	else if (KEY_PRESS(VK_LBUTTON))
	{
		_chargeTime += DELTA_TIME;

		if (_chargeTime > 1)
		{
			_chargeTime = 0;
			if (_chargeCount < _vals[0])
				_chargeCount++;

			TileMap::GetInstance()->Hoeing(_point, _chargeCount);
		}
	}
	else if (KEY_UP(VK_LBUTTON))
	{
		Player::GetInstance()->AddStamina(_vals[1]);

		TileMap::GetInstance()->Hoeing(_point, _chargeCount);

	}
}

void Item::Water()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_chargeCount = 0;
		_chargeTime = 0;
		_point = W_MOUSE_POS;
	}
	else if (KEY_PRESS(VK_LBUTTON))
	{
		_chargeTime += DELTA_TIME;

		if (_chargeTime > 1)
		{
			_chargeTime = 0;
			if (_chargeCount < _vals[0])
				_chargeCount++;

			TileMap::GetInstance()->Hoeing(_point, _chargeCount);
		}
	}
	else if (KEY_UP(VK_LBUTTON))
	{
		Player::GetInstance()->AddStamina(_vals[1]);

		TileMap::GetInstance()->Watering(_point, _chargeCount);

		//Player::GetInstance()->
	}
	
}

void Item::Axe()
{
}

void Item::PickAxe()
{
}

void Item::Fishing()
{
}

void Item::Weapon()
{
}

void Item::Eat()
{
}

void Item::Seed()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_point = W_MOUSE_POS;
		auto tile = dynamic_pointer_cast<ArableTile>(TileMap::GetInstance()->GetFocusedTile());
		if (tile->GetPlantable())
			tile->Plant(_subName);
	}
}

void Item::Fertilizer()
{
}
