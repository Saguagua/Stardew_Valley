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
	_renderer = make_shared<TextureRect>(L"Resource/Object/Objects.png", DATA->GetObjectMaxFrame(), Vector2(20, 20));
	
	for (int i = 0; i < 60; i++)
	{
		shared_ptr<DropItem> item = make_shared<DropItem>();
		_dropItems.push_back(item);
	}
}

shared_ptr<GameObject> ObjectSpawner::CreateObj(int objCode, short count)
{
	vector<short> vals = DATA->GetObjectInfo(objCode)->GetVals();

	switch (vals[0])
	{
	case ObjectInfo::BREAKABLE:
	{
		return make_shared<BreakableItem>(objCode, vals[1], vals[2], vals[3], vals[4], vals[5], vals[6]);
	}
	case ObjectInfo::EATABLE:
	{
		return make_shared<EatableItem>(objCode, vals);
	}
	case ObjectInfo::PICKABLE:
	{
		return make_shared<PickableItem>(objCode, vals[1], vals[2], vals[7]);
	}
	case ObjectInfo::AXE:
	{
		//return make_shared<Axe>(itemCode);
	}
	case ObjectInfo::PICKAXE:
	{
		return make_shared<PickAxe>(objCode, vals[1], vals[2], vals[3]);
	}
	case ObjectInfo::HOE:
	{
		//return make_shared<Hoe>(itemCode);
	}
	case ObjectInfo::WATERINGCAN:
	{
		//return make_shared<WateringCan>(itemCode);
	}
	case ObjectInfo::FISHINGROD:
	{
		//return make_shared<FishingRod>(itemCode);
	}
	case ObjectInfo::BLANK:
	{
		return make_shared<GameObject>(objCode, vals[1]);
	}

	default:
		break;
	}

    return make_shared<GameObject>(objCode, vals[1], vals[7], count);
}

void ObjectSpawner::Update()
{
	for (auto dropItem : _dropItems)
	{
		if (!dropItem->IsActive())
			continue;
		dropItem->Update();
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
				vector<short> vals = DATA->GetObjectInfo(objCode)->GetVals();
				_dropItems[i]->Spawn(pos, objCode, vals[1], vals[2]);
				break;
			}
		}
	}
}
