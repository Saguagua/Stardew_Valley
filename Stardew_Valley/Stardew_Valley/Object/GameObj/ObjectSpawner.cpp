#include "framework.h"
#include "ObjType/DeployableObj/DeployableObject.h"
#include "ObjType/DeployableObj/BreakableItem.h"
#include "ObjType/DeployableObj/PickableItem.h"
#include "ObjType/DeployableObj/DropItem.h"
#include "ObjType/DeployableObj/Crop.h"
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
		//_crops.push_back(make_shared<Crop>(objName, Vector2(1,1), 0, 2));
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

shared_ptr<Crop> ObjectSpawner::CreateCrop(string name, short progress, short quality, short level)
{
	short period = 15;
	vector<short> vals;

	vals.push_back(period);
	vals.push_back(progress);
	vals.push_back(quality);
	vals.push_back(level);
	shared_ptr<Crop> crop = make_shared<Crop>(name, Vector2(1, 1), vals);
	_crops.push_back(crop);
	return crop;
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

	for (int i = 0; i < count; i++)
	{
		for (int i = 0; i < _dropItems.size(); i++)
		{
			if (!_dropItems[i]->IsActive())
			{
				_dropItems[i]->Spawn(dropName, itemName, pos);
				break;
			}
		}
	}
}
