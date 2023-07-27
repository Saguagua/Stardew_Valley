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

shared_ptr<GameObject> ObjectSpawner::CreateObj(int itemCode, short count)
{
	shared_ptr<ObjectInfo> info = DATA->GetObjectInfo(itemCode);

	switch (info->GetVals()[0])
	{
	case ObjectInfo::BREAKABLE:
	{
		//return make_shared<BreakableItem>(itemCode, 1, info->GetHp());
	}
	case ObjectInfo::EATABLE:
	{
		//return make_shared<EatableItem>(itemCode, 1);
	}
	case ObjectInfo::PICKABLE:
	{
		//return make_shared<PickableItem>(itemCode);
	}
	case ObjectInfo::AXE:
	{
		//return make_shared<Axe>(itemCode);
	}
	case ObjectInfo::PICKAXE:
	{
		//return make_shared<PickAxe>(itemCode);
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

	default:
		break;
	}

    return make_shared<GameObject>(itemCode, count);
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

void ObjectSpawner::ActiveDropItem(Vector2 pos, int itemCode, int count)
{
	for (int i = 0; i < count; i++)
	{
		int index = 0;

		for (int i = 0; i < _dropItems.size(); i++)
		{
			if (!_dropItems[i]->IsActive())
			{
				index = i;
				break;
			}
		}

		if (index != _dropItems.size()-1)
		{
			_dropItems[index]->Spawn(pos, itemCode);
		}
		else 
			break;
	}
}
