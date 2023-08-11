#include "framework.h"
#include "ObjType/DeployableObj/DeployableObject.h"
#include "ObjType/DeployableObj/BreakableItem.h"
#include "ObjType/DeployableObj/PickableItem.h"
#include "ObjType/DeployableObj/DropItem.h"
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
	_objTable = (DATA->GetObjectInfos());

	for (int i = 0; i < 60; i++)
	{
		shared_ptr<DropItem> item = make_shared<DropItem>();
		_dropItems.push_back(item);
	}

	for (int i = 0; i < 30; i++)
	{
		_breakObjs.push_back(make_shared<BreakableItem>());
	}

	for (int i = 0; i < 30; i++)
	{
		_pickObjs.push_back(make_shared<PickableItem>());
	}

	for (int i = 0; i < 30; i++)
	{
		_crops.push_back(make_shared<Crop>());
	}
}

void ObjectSpawner::CreateObj(string objName, int type, Vector2 pos)
{
	vector<int> vals = _objTable[objName]->GetVals();

	switch (type)
	{
	case ObjectInfo::BREAKABLE:
	{
		for (int i = 0; i < _breakObjs.size(); i++)
		{
			if (!_breakObjs[i]->IsActive())
			{
				_breakObjs[i]->S
			}
		}
	}
	case ObjectInfo::PICKABLE:
	{
		//_objects.push_back(make_shared<PickableItem>(objName, vals[1], vals[2], vals[7]));
	}

	default:
		break;
	}
}

shared_ptr<class Crop> ObjectSpawner::CreateCrop(string name, int progress, int quality)
{
	return shared_ptr<class Crop>();
}

shared_ptr<GameObject> ObjectSpawner::CreateItem(string objName, int type, short count)
{
	vector<int> vals = _objTable[objName]->GetVals();

	switch (type)
	{
	case ObjectInfo::NONE:
	{

		break;
	}
	case ObjectInfo::EATABLE:
	{

		break;
	}
	case ObjectInfo::AXE: 
	{
		break;
	}
	case ObjectInfo::PICKAXE:
	{
		break;
	}
	case ObjectInfo::HOE:
		{

			break; 
		}
	case ObjectInfo::WATERINGCAN:
		break;
	case ObjectInfo::FISHINGROD:
		break;
	case ObjectInfo::WEAPON:
		break;
	case ObjectInfo::SEED:
		break;
	case ObjectInfo::FARMMING:
		break;
	default:
		break;
	}

	return shared_ptr<GameObject>();
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
		_renderer->SetCurFrame(dropItem->GetCode());
		_renderer->Render();
	}
}

void ObjectSpawner::ActiveDropItem(Vector2 pos, int objCode, int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int i = 0; i < _dropItems.size(); i++)
		{
			if (!_dropItems[i]->IsActive())
			{
				/*vector<short> vals = DATA->GetObjectInfo(objCode)->GetVals();
				_dropItems[i]->Spawn(pos, objCode, vals[1], vals[2]);*/
				break;
			}
		}
	}
}
