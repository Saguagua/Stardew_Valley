#include "framework.h"
#include "ObjType\DeployableObj\SpawnInfo.h"
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
#include "../../Data/ObjectInfo.h"
#include "ObjectSpawner.h"

ObjectSpawner* ObjectSpawner::_instance = nullptr;

ObjectSpawner::ObjectSpawner()
{
	_renderer = make_shared<LightTextureRect>(L"Resource/Object/Objects.png", DATA->GetObjectMaxFrame(), Vector2(40, 40));
	_deployTable = DATA->GetDeployInfos();
	_dropTable = DATA->GetDropInfos();
	_itemTable = DATA->GetItemInfos();

	for (int i = 0; i < 60; i++)
	{
		_dropItems.push_back(make_shared<DropItem>());
	}
}

shared_ptr<DeployableObject> ObjectSpawner::CreateObj(string objName)
{
	if (objName == "BLANK")
		return nullptr;
	vector<short> vals = _deployTable[objName]->GetVals();
	shared_ptr<DeployableObject> obj;
	switch (_deployTable[objName]->GetType())
	{
	case DeployableObject::BREAK:
	{
		 obj = make_shared<BreakableItem>(objName, Vector2(1,1));
		return obj;
	}
	case DeployableObject::PICK:
	{
		obj = make_shared<PickableItem>(objName);
		return obj;
	}
	case DeployableObject::BLANK:
	{
		return nullptr;
	}

	default:
		break;
	}
}

shared_ptr<Crop> ObjectSpawner::CreateCrop(string name, int progress, int quality)
{
	return make_shared<Crop>(name, Vector2(1,1));
}

shared_ptr<Item> ObjectSpawner::CreateItem(string objName, short count)
{
	vector<short> vals = _itemTable[objName]->GetVals();

	switch (vals[0])
	{
	case Item::NONE:
	{
		return make_shared<Item>(Item::Type::NONE, objName, vals[1]);
	}
	case Item::EATABLE:
	{
		return make_shared<EatableItem>(objName, vals);
	}
	case Item::AXE:
	{
		return make_shared<Axe>(objName);
	}
	case Item::PICKAXE:
	{
		return make_shared<PickAxe>(objName);
		break;
	}
	case Item::HOE:
		{

			break; 
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

	return make_shared<Item>(Item::Type::NONE, objName, vals[0]);
}

void ObjectSpawner::Update()
{
	for (auto dropItem : _dropItems)
	{
		if (!dropItem->IsActive())
			continue;
		dropItem->Update();
		if (dropItem->GetCollider()->IsCollision(_playerInfo->GetCollider()))
			dropItem->Interaction();
		else if (dropItem->GetArea()->IsCollision(_playerInfo->GetCollider()))
		{
			Vector2 dir = _playerInfo->GetWorldPos() - dropItem->GetWorldPos();
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
