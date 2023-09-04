#include "framework.h"
#include "Object\GameObj\Creature\Player\PlayerImproved.h"
#include "ObjectSpawner.h"

ObjectSpawner* ObjectSpawner::_instance = nullptr;

ObjectSpawner::ObjectSpawner()
{
	_renderer = make_shared<Sprite>(XMLPATH1, "BLANK", Vector2(20, 20), SpriteType::OBJECT);

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
		 obj = make_shared<BreakableItem>(objName, Vector2(0,0), vals[0], vals[1]);
		 break;
	}
	case DeployableObject::PICK:
	{
		obj = make_shared<PickableItem>(objName, Vector2(0, 0));
		break;
	}
	case DeployableObject::BLANK:
	{
		return nullptr;
	}
	case DeployableObject::CROP:
	{
		//vector<short> values = _cropTable[objName];
		short period = 6;
		vector<short> cvals;

		cvals.push_back(period);
		cvals.push_back(5);
		cvals.push_back(2);
		cvals.push_back(0);

		
		obj = make_shared<Crop>(objName, Vector2(0,0), cvals);
		break;
	}
	default:
		break;
	}

	return obj;
}

void ObjectSpawner::CreateObj(shared_ptr<MapInfo> map, int index, string objName, short val1, short val2)
{
	vector<shared_ptr<Tile>>& tiles = map->GetInfos();

	Vector2 size = _deployTable[objName]->GetSize();
	Vector2 tmp;
	tmp.x = TILE_SIZE.x * (size.x * 0.5f) - TILE_SIZE.x * 0.5f;
	tmp.y = TILE_SIZE.y * (size.y * 0.5f) - TILE_SIZE.y * 0.5f;

	Vector2 centerPos = tiles[index]->GetCenterPos() + tmp;

	shared_ptr<DeployableObject> obj;

	switch (_deployTable[objName]->GetType())
	{
	case DeployableObject::BREAK:
	{
		obj = make_shared<BreakableItem>(objName, centerPos, val1);
		break;
	}
	case DeployableObject::PICK:
	{
		obj = make_shared<PickableItem>(objName, centerPos);
		break;
	}
	case DeployableObject::WALL:
	{
		obj = make_shared<Wall>(objName, centerPos);
		break;
	}
	case DeployableObject::BLANK:
	{
		return;
	}
	default:
		break;
	}

	tiles[index]->SetObjName(objName);

	Vector2 mapSize = map->GetSize();

	for (int i = 0; i < size.y; i++)
	{
		for (int j = index; j < index + size.x; j++)
		{
			int index = j + i * mapSize.x;
			if (index >= mapSize.x * mapSize.y)
				continue;
			tiles[j + i * mapSize.x]->SetObj(obj);
		}
	}

}

Crop* ObjectSpawner::CreateCrop(string name, short progress, short quality, short level)
{
	short period = 6;
	vector<short> vals;

	vals.push_back(period);
	vals.push_back(progress);
	vals.push_back(quality);
	vals.push_back(level);

	Crop* crop = new Crop(name, Vector2(0, 0), vals);
	_crops.push_back(crop);

	return crop;
}

void ObjectSpawner::Update_Crops()
{
	for (std::list<Crop*>::iterator iter = _crops.begin(); iter != _crops.end(); )
	{
		if ((*iter)->GetName() == "BLANK")
		{
			iter = _crops.erase(iter);
		}
		else
		{
			(*iter)->Update();
			++iter;
		}
	}
}

void ObjectSpawner::Update()
{
	for (auto dropItem : _dropItems)
	{
		if (!dropItem->IsActive())
			continue;

		if (!dropItem->IsPoping())
		{
			for (auto other : _dropItems)
			{
				if (!other->IsActive())
					continue;
				if (other == dropItem)
					continue;

				dropItem->GetCollider()->Block(other->GetCollider());
			}
			if (!_player.expired())
			{
				if (dropItem->GetCollider()->IsCollision(_player.lock()->GetCollider()))
				{
					dropItem->Interaction();
				}
				else if (dropItem->GetCollider()->IsCollision(_player.lock()->GetMagnatic()))
				{
					Vector2 dir = _player.lock()->GetWorldPos() - dropItem->GetWorldPos();
					dir = dir.Normalize();
					dropItem->AddPos(dir * 100 * DELTA_TIME);
				}
			}
		}

		dropItem->Update();

	}
}

void ObjectSpawner::Render()
{
	for (auto dropItem : _dropItems)
	{
		if (!dropItem->IsActive())
			continue;
		dropItem->Render(_renderer);
	}
	
}

void ObjectSpawner::SetPlayer(shared_ptr<PlayerImproved> player)
{
	_player = player;
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
