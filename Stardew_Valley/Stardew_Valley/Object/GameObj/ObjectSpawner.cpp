#include "framework.h"
#include "ObjType/BreakableItem.h"
#include "ObjType/EatableItem.h"
#include "ObjType/PickableItem.h"
#include "ObjType/DropItem.h"
#include "ObjType/Axe.h"
#include "ObjType/PickAxe.h"
#include "ObjType/Hoe.h"
#include "ObjType/WateringCan.h"
#include "ObjType/FishingRod.h"
#include "../../Data/ObjectInfo.h"
#include "ObjectSpawner.h"

ObjectSpawner* ObjectSpawner::_instance = nullptr;

ObjectSpawner::ObjectSpawner()
{
	_renderer = make_shared<LightTextureRect>(L"Resource/Object/Objects.png", DATA->GetObjectMaxFrame(), Vector2(40, 40));
	
	for (int i = 0; i < 60; i++)
	{
		shared_ptr<DropItem> item = make_shared<DropItem>();
		_dropItems.push_back(item);
	}
}

void ObjectSpawner::CreateObj(string objName, int type, Vector2 pos)
{
	vector<int> vals = _objTable[objName]->GetVals();

	switch (type)
	{
	case ObjectInfo::BREAKABLE: //pos
	{
		//return make_shared<BreakableItem>(objName, vals[1], vals[2], vals[3], vals[4], vals[5], vals[6]);
	}
	case ObjectInfo::PICKABLE:
	{
		//return make_shared<PickableItem>(objName, vals[1], vals[2], vals[7]);
	}

	default:
		break;
	}
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
