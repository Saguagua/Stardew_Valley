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

void Item::Use()
{
	switch (_type)
	{
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
	case Item::AXE:
	case Item::PICKAXE:
	{
		Break();
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
	case Item::FACILITY:
	{
		Collocate();
		break;
	}
	case Item::FERTILIZER:
	{
		Fertilizer();
		break;
	}
	case Item::WEAPON:
	{
		Weapon();
		break;
	}
	}
}

void Item::Charging()
{
	_chargeTime += DELTA_TIME;

	if (_chargeTime >= _timeMax)
	{
		_chargeTime = 0;

		if (_chargeLevel < _chargeMax)
		{
			_chargeLevel += _levelPlus;

			if (_type != FISHINGROD)
				_map.lock()->Charging(_player.lock()->GetWorldPos(), _point, _chargeLevel);
		}
	}
}

void Item::StartCharging(int chargLevelInitial, float timeMax , int chargeMax, int levelPlus)
{
	_chargeTime = 0;
	_timeMax = timeMax;
	_chargeMax = chargeMax;
	_levelPlus = levelPlus;
	_chargeLevel = chargLevelInitial;
	_point = W_MOUSE_POS;
}

void Item::Hoe()
{
	_player.lock()->AddStamina(_vals[1]);
	_map.lock()->Hoeing(_player.lock()->GetWorldPos(), _point, _chargeLevel);
	_player.lock()->SetFreeze(false);
	_player.lock()->SetToolActive(false);
}

void Item::Water()
{
	_player.lock()->AddStamina(_vals[1]);
	_map.lock()->Watering(_player.lock()->GetWorldPos(), _point, _chargeLevel);
	_player.lock()->SetFreeze(false);
	_player.lock()->SetToolActive(false);
}

void Item::Break()
{
	_point = W_MOUSE_POS;

	_player.lock()->AddStamina(_vals[1]);

	shared_ptr<DeployableObject> obj = _map.lock()->GetFocusedTile(_player.lock()->GetWorldPos(), _point)->GetObj();
	auto breakObj = dynamic_pointer_cast<BreakableItem>(obj);

	if (breakObj != nullptr)
	{
		breakObj->GetDamage(shared_from_this());
	}

	_player.lock()->SetFreeze(false);
	_player.lock()->SetToolActive(false);
}

void Item::Fishing()
{
	if (FishingSystem::GetInstance()->GetStep() != FishingSystem::Step::THROW)
		return;

	_player.lock()->AddStamina(_vals[1]);
	
	int dir = _player.lock()->GetDirection();
	Vector2 direction;
	Vector2 originPos = _player.lock()->GetWorldPos();
	Vector2 targetPos = originPos;


	if (dir == SIDE)
	{
		float lr = _player.lock()->GetCollider()->GetWorldScale().x;
		direction.x = 1 * lr;
		direction.y = 0;
		targetPos.x += (_chargeLevel * lr);
	}
	else if (dir == FRONT)
	{
		direction.x = 0;
		direction.y = -1;
		targetPos.y -= _chargeLevel;
	}
	else if (dir == BACK)
	{
		direction.x = 0;
		direction.y = 1;
		targetPos.y += _chargeLevel;
	}

	FishingSystem::GetInstance()->HookSetting(direction, _chargeLevel);
	FishingSystem::GetInstance()->ActiveFishingHook();
}

void Item::Weapon()
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


	_player.lock()->SetFreeze(false);
	_player.lock()->SetToolActive(false);
	_player.lock()->SetAttacking(false);
}

void Item::Eat()
{
	
	_player.lock()->AddMaxHP(_vals[0]);
	_player.lock()->AddMaxStamina(_vals[1]);
	_player.lock()->AddHP(_vals[2]);
	_player.lock()->AddStamina(_vals[3]);

	_count--;
	
	if (_count <= 0)
	{
		SetItem("BLANK", 0);
	}
	
	_player.lock()->SendToSubscribers(PlayerSubscribe::ITEMS);
	
}

void Item::Seed()
{
	_point = W_MOUSE_POS;
	auto tile = dynamic_pointer_cast<ArableTile>(_map.lock()->GetFocusedTile(_player.lock()->GetWorldPos(), _point));

	if (tile == nullptr)
		return;

	if (!tile->GetPlantable() || tile->GetObj() != nullptr)
		return;

	OBJECT_SPAWNER->CreateObj(_map.lock()->GetcurrentMapInfo(),
		_map.lock()->GetFocusedIndex(_player.lock()->GetWorldPos(), _point), _subName, 1, 1);
	_count--;

	if (_count <= 0)
	{
		SetItem("BLANK", 0);
	}

	_player.lock()->SendToSubscribers(PlayerSubscribe::ITEMS);
}

void Item::Fertilizer()
{
}

void Item::Collocate()
{
	auto tile = _map.lock()->GetFocusedTile(_player.lock()->GetWorldPos(), W_MOUSE_POS);

	if (tile->GetObj())
		return;
	if (DATA->GetTileInfo(tile->GetName()) & TileType::BLOCK)
		return;
	auto vals = DATA->GetDeployInfo(_name)->GetVals();
	OBJECT_SPAWNER->CreateObj(_map.lock()->GetcurrentMapInfo(), tile->_mapIndex, _name, vals[0], vals[1]);
	_count--;

	if (_count == 0)
	{
		SetItem("BLANK",0);
	}

	_player.lock()->SendToSubscribers(PlayerSubscribe::ITEMS);
}