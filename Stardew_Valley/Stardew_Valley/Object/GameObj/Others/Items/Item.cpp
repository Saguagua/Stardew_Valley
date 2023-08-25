#include "framework.h"
#include "../../../Tile/TileType/ArableTile.h"
#include "../../../Tile/TileType/FishableTile.h"
#include "Item.h"


void Item::SetItem(string name, short count)
{
	shared_ptr<ItemInfo> info = DATA->GetItemInfo(name);

	_name = name;
	_count = count;
	_subName = info->GetSubName();
	_price = info->GetPrice();
	_type = info->GetType();
	_vals = info->GetVals();
}

bool Item::AddCount()
{
	if (_count < 64)
	{
		_count++;
		return true;
	}
	return false;
}

void Item::Hoe(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m)
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

			m->Charging(p->GetWorldPos(), _point, _chargeCount);
		}
	}
	else if (KEY_UP(VK_LBUTTON))
	{
		p->AddStamina(_vals[1]);
		m->Hoeing(p->GetWorldPos(), _point, _chargeCount);
	}
}

void Item::Water(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m)
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

			m->Charging(p->GetWorldPos(), _point, _chargeCount);
		}
	}
	else if (KEY_UP(VK_LBUTTON))
	{
		p->AddStamina(_vals[1]);
		m->Watering(p->GetWorldPos(), _point, _chargeCount);
	}
}

void Item::Break(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m)
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_point = W_MOUSE_POS;

		p->AddStamina(_vals[1]);

		shared_ptr<DeployableObject> obj = m->GetFocusedTile(p->GetWorldPos(), _point)->GetObj();
		auto breakObj = dynamic_pointer_cast<BreakableItem>(obj);

		if (obj != nullptr)
		{
			obj->Interaction();
		}
	}
}

void Item::Fishing(shared_ptr<PlayerImproved> p)
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_chargeCount = 0;
		_chargeTime = 0;
		_point = W_MOUSE_POS;
	}
	else if (KEY_PRESS(VK_LBUTTON))
	{
		if (_chargeCount < 150)
			_chargeCount+=5;
	}
	else if (KEY_UP(VK_LBUTTON))
	{
		p->AddStamina(_vals[1]);
		int dir = p->GetDirection();
		Vector2 direction;
		Vector2 originPos = p->GetWorldPos();
		Vector2 targetPos = originPos;

		if (dir == SIDE)
		{
			float lr = p->GetCollider()->GetWorldScale().x;
			direction.x = 1 * lr;
			direction.y = 0;
			targetPos.x += (_chargeCount * lr);
		}
		else if (dir == FRONT)
		{
			direction.x = 0;
			direction.y = -1;
			targetPos.y -= _chargeCount;
		}
		else if (dir == BACK)
		{
			direction.x = 0;
			direction.y = 1;
			targetPos.y += _chargeCount;
		}

		OBJECT_SPAWNER->ActiveFishingHook(originPos, targetPos , direction, 200);
	}
}

void Item::Weapon(shared_ptr<PlayerImproved> p)
{
}

void Item::Eat(shared_ptr<PlayerImproved> p)
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		p->AddMaxHP(_vals[0]);
		p->AddMaxStamina(_vals[1]);
		p->AddHP(_vals[2]);
		p->AddStamina(_vals[3]);
		
		_count--;

		if (_count >= 0)
		{
			SetItem("BLANK", 0);
		}
	}
}

void Item::Seed(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m)
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_point = W_MOUSE_POS;
		auto tile = dynamic_pointer_cast<ArableTile>(m->GetFocusedTile(p->GetWorldPos(), _point));
		if (tile->GetPlantable() && tile->GetCrop() != nullptr)
			tile->Plant(_subName);
	}
}

void Item::Fertilizer(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m)
{
}
