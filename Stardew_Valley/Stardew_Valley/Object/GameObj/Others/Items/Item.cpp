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

void Item::Use(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m)
{
	switch (_type)
	{
	case Item::EATABLE:
	{
		Eat(p);
		break;
	}
	case Item::FISHINGROD:
	{
		Fishing(p);
		break;
	}
	case Item::HOE:
	{
		Hoe(p, m);
		break;
	}
	case Item::AXE:
	case Item::PICKAXE:
	{
		Break(p, m);
		break;
	}
	case Item::WATERINGCAN:
	{
		Water(p, m);
		break;
	}
	case Item::SEED:
	{
		Seed(p, m);
		break;
	}
	case Item::FACILITY:
	{
		Collocate(p, m);
		break;
	}
	case Item::FERTILIZER:
	{
		Fertilizer(p, m);
		break;
	}
	case Item::WEAPON:
	{
		Weapon(p);
		break;
	}
	}
}

void Item::Charging()
{
	_chargeTime += DELTA_TIME;

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
	
	_point = W_MOUSE_POS;

	p->AddStamina(_vals[1]);

	shared_ptr<DeployableObject> obj = m->GetFocusedTile(p->GetWorldPos(), _point)->GetObj();
	auto breakObj = dynamic_pointer_cast<BreakableItem>(obj);

	if (breakObj != nullptr)
	{
		breakObj->GetDamage(shared_from_this());
	}
}

void Item::Fishing(shared_ptr<PlayerImproved> p)
{
	if (FishingSystem::GetInstance()->GetStep() != FishingSystem::Step::THROW)
		return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		_chargeCount = 300;
		_chargeTime = 0;
		_point = W_MOUSE_POS;
	}
	else if (KEY_PRESS(VK_LBUTTON))
	{
		if (_chargeCount < 700)
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

		FishingSystem::GetInstance()->HookSetting(direction, _chargeCount);
	}
}

void Item::Weapon(shared_ptr<PlayerImproved> p)
{
	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	if (p->_isAttacking)
	//		return;
	//	p->_isAttacking = true;
	//	p->SetDirection(W_MOUSE_POS);
	//	int direction = p->GetDirection();

	//	if (direction == FRONT)
	//		p->_weaponSlot->SetAngle(XM_PIDIV2);

	//	else if (direction == SIDE)
	//		p->_weaponSlot->SetAngle(XM_PI);

	//	else if (direction == BACK)
	//		p->_weaponSlot->SetAngle(-XM_PIDIV2);

	//	p->_attackCount = 0.0f;
	//	p->_isAttacking = true;
	//}
}

void Item::Eat(shared_ptr<PlayerImproved> p)
{
	
	p->AddMaxHP(_vals[0]);
	p->AddMaxStamina(_vals[1]);
	p->AddHP(_vals[2]);
	p->AddStamina(_vals[3]);
	
	_count--;
	
	if (_count <= 0)
	{
		SetItem("BLANK", 0);
	}
	
	p->SendToSubscribers(PlayerSubscribe::ITEMS);
	
}

void Item::Seed(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m)
{
	_point = W_MOUSE_POS;
	auto tile = dynamic_pointer_cast<ArableTile>(m->GetFocusedTile(p->GetWorldPos(), _point));

	if (tile == nullptr)
		return;

	if (!tile->GetPlantable() || tile->GetObj() != nullptr)
		return;

	OBJECT_SPAWNER->CreateObj(m->GetcurrentMapInfo(), m->GetFocusedIndex(p->GetWorldPos(), _point), _subName, 1, 1);
	_count--;

	if (_count <= 0)
	{
		SetItem("BLANK", 0);
	}

	p->SendToSubscribers(PlayerSubscribe::ITEMS);
}

void Item::Fertilizer(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m)
{
}

void Item::Collocate(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m)
{
	auto tile = m->GetFocusedTile(p->GetWorldPos(), W_MOUSE_POS);

	if (tile->GetObj())
		return;
	if (DATA->GetTileInfo(tile->GetName()) & TileType::BLOCK)
		return;
	auto vals = DATA->GetDeployInfo(_name)->GetVals();
	OBJECT_SPAWNER->CreateObj(m->GetcurrentMapInfo(), tile->_mapIndex, _name, vals[0], vals[1]);
	_count--;

	if (_count == 0)
	{
		SetItem("BLANK",0);
	}

	p->SendToSubscribers(PlayerSubscribe::ITEMS);
}