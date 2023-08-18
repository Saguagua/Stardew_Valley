#include "framework.h"
#include "ObjType\DeployableObj\SpawnInfo.h"
#include "../BasicObj/Sprite.h"
#include "ObjType/DeployableObj/DeployableObject.h"
#include "ObjType/DeployableObj/BreakableItem.h"
#include "ObjType/DeployableObj/PickableItem.h"
#include "ObjType/DeployableObj/DropItem.h"
#include "ObjType/DeployableObj/Crop.h"
#include "ObjType/Items/EatableItem.h"
#include "ObjType/Items/Axe.h"
#include "ObjType/Items/PickAxe.h"
#include "ObjType/Items/Hoe.h"
#include "ObjType/Items/WateringCan.h"
#include "ObjType/Items/FishingRod.h"
#include "ObjectSpawner.h"

ObjectSpawner* ObjectSpawner::_instance = nullptr;

ObjectSpawner::ObjectSpawner()
{
	_renderer = make_shared<Sprite>(L"Resource/Object/Objects.png", "Potato", TILE_SIZE);

	for (int i = 0; i < 60; i++)
	{
		_dropItems.push_back(make_shared<DropItem>());
	}
}

shared_ptr<DeployableObject> ObjectSpawner::CreateObj(string objName)
{
	vector<short> vals = _deployTable[objName]->GetVals();
	shared_ptr<DeployableObject> obj;

	switch (_deployTable[objName]->GetType())
	{
	case DeployableObject::BREAK:
	{
		 obj = make_shared<BreakableItem>(objName, Vector2(1,1));
		 break;
	}
	case DeployableObject::PICK:
	{
		obj = make_shared<PickableItem>(objName);
		break;
	}
	case DeployableObject::CROP:
	{
		_crops.push_back(make_shared<Crop>(objName, Vector2(1,1), 0, 2));
		break;
	}
	case DeployableObject::BLANK:
	{
		return nullptr;
	}

	default:
		break;
	}
	// ªÁ¿Ã¡Ó ππΩ√≤§
	return obj;
}

void ObjectSpawner::CreateObj(shared_ptr<MapInfo> map, int index, string objName, short val1, short val2)
{
	vector<shared_ptr<Tile>>& tiles = map->GetInfos();
	Vector2 mapSize = map->GetSize();
	Vector2 size = _deployTable[objName]->GetSize();
	shared_ptr<DeployableObject> obj;
	tiles[index]->SetObjName(objName);

	switch (_deployTable[objName]->GetType())
	{
	case DeployableObject::BREAK:
	{
		obj = make_shared<BreakableItem>(objName, size, val1);
		break;
	}
	case DeployableObject::PICK:
	{
		obj = make_shared<PickableItem>(objName);
		break;
	}
	case DeployableObject::BLANK:
	{
		return;
	}
	default:
		break;
	}

	for (int i = 0; i < size.y; i++)
	{
		for (int j = index; j < size.x; j++)
		{
			tiles[j + i * mapSize.x]->SetObj(obj);
		}
	}

}

shared_ptr<Crop> ObjectSpawner::CreateCrop(string name, int progress, int quality)
{
	return make_shared<Crop>(name, Vector2(1,1), progress, quality);
}

shared_ptr<Item> ObjectSpawner::CreateItem(string objName, short count)
{
	shared_ptr<ItemInfo> item = _itemTable[objName];

	switch (item->GetType())
	{
	case Item::NONE:
	{
		return make_shared<Item>(Item::Type::NONE, objName, item->GetPrice());
	}
	case Item::EATABLE:
	{
		return make_shared<EatableItem>(objName, item->GetPrice(), item->GetVals());
	}
	case Item::AXE:
	{
		return make_shared<Axe>(objName, item->GetPrice());
	}
	case Item::PICKAXE:
	{
		return make_shared<PickAxe>(objName);
	}
	case Item::HOE:
	{
		return make_shared<Hoe>(objName, item->GetPrice(), item->GetVals()[0]);
	}
	case Item::WATERINGCAN:
		break;
	case Item::FISHINGROD:
		break;
	case Item::WEAPON:
		break;
	case Item::SEED:
		break;
	case Item::FRTI:
		break;
	default:
		break;
	}

	return make_shared<Item>(Item::Type::NONE, objName, item->GetPrice());
}

void ObjectSpawner::Update()
{
	for (auto dropItem : _dropItems)
	{
		if (!dropItem->IsActive())
			continue;
		dropItem->Update();
		if (dropItem->GetCollider()->IsCollision(Player::GetInstance()->GetCollider()))
			dropItem->Interaction();
		else if (dropItem->GetArea()->IsCollision(Player::GetInstance()->GetCollider()))
		{
			Vector2 dir = Player::GetInstance()->GetWorldPos() - dropItem->GetWorldPos();
			dir = dir.Normalize();
			dropItem->AddPos(dir * 100 * DELTA_TIME);
		}
	}
}

void ObjectSpawner::Render()
{
	for (auto dropItem : _dropItems)
	{
		if (!dropItem->IsActive())
			continue;
		dropItem->Render();
		//_renderer->SetCurFrame(dropItem->GetCode());
		_renderer->Render();
	}
}

void ObjectSpawner::ActiveDropItem(string dropName, string itemName, Vector2 pos, int count)
{
	struct Info
	{
		Info(string name, Vector2 pos)
			:_itemName(name), _pos(pos)
		{}
		Vector2 _pos;
		string _itemName;
	};

	Info* info = new Info(itemName, pos);
	shared_ptr<SpawnInfo> spawnInfo = make_shared<SpawnInfo>(info);

	for (int i = 0; i < count; i++)
	{
		for (int i = 0; i < _dropItems.size(); i++)
		{
			if (!_dropItems[i]->IsActive())
			{
				_dropItems[i]->Spawn(dropName, spawnInfo);
				break;
			}
		}
	}
}
