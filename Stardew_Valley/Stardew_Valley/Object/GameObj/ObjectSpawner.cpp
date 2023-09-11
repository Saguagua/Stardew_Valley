#include "framework.h"
#include "Object\GameObj\Creature\Player\PlayerImproved.h"
#include "ObjectSpawner.h"

ObjectSpawner* ObjectSpawner::_instance = nullptr;

ObjectSpawner::ObjectSpawner()
{
	_renderer = make_shared<Sprite>("BLANK", Vector2(20, 20), SpriteType::OBJECT);

	for (int i = 0; i < 60; i++)
	{
		_dropItems.push_back(make_shared<DropItem>());
	}
}
//
//shared_ptr<DeployableObject> ObjectSpawner::CreateObj(string objName)
//{
//	vector<short> vals = _deployTable[objName]->GetVals();
//	shared_ptr<DeployableObject> obj;
//
//	switch (_deployTable[objName]->GetType())
//	{
//	case DeployableObject::BREAK:
//	{
//		 obj = make_shared<BreakableItem>(objName, Vector2(0,0), vals[0], vals[1]);
//		 break;
//	}
//	case DeployableObject::PICK:
//	{
//		obj = make_shared<PickableItem>(objName, Vector2(0, 0));
//		break;
//	}
//	case DeployableObject::BLANK:
//	{
//		return nullptr;
//	}
//	case DeployableObject::CROP:
//	{
//		//vector<short> values = _cropTable[objName];
//		short period = 6;
//		vector<short> cvals;
//
//		cvals.push_back(period);
//		cvals.push_back(5);
//		cvals.push_back(2);
//		cvals.push_back(0);
//
//		
//		obj = make_shared<Crop>(objName, Vector2(0,0), cvals);
//		break;
//	}
//	default:
//		break;
//	}
//
//	return obj;
//}

void ObjectSpawner::CreateObj(shared_ptr<MapInfo> map, int index, string objName, short val1, short val2)
{
	vector<shared_ptr<Tile>>& tiles = map->GetInfos();

	Vector2 size = _deployTable[objName]->GetSize();

	Vector2 tmp;

	if (size.x >= 1 && size.y >= 1)
	{
		tmp.x = TILE_SIZE.x * (size.x * 0.5f) - TILE_SIZE.x * 0.5f;
		tmp.y = TILE_SIZE.y * (size.y * 0.5f) - TILE_SIZE.y * 0.5f;

	}
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
	case DeployableObject::CROP:
	{
		vector<short> val;
		val.push_back(10);//period
		val.push_back(0);  //pro
		val.push_back(1);  //qual
		val.push_back(0);
		obj = make_shared<Crop>(objName, centerPos, val);
		break;
	}
	case DeployableObject::DOOR:
	{
		obj = make_shared<Door>(objName, centerPos);
		break;
	}
	case DeployableObject::BED:
	{
		obj = make_shared<Bed>(objName, centerPos);
		break;
	}
	case DeployableObject::LIGHT:
	{
		shared_ptr<LightInfo> info = make_shared<LightInfo>(XMFLOAT4(1000, 1000, 0, 1), XMFLOAT4(centerPos.x, centerPos.y, 0, 0));

		int lightIndex = map->AddLight(info);

		if (lightIndex == -1)
			return;

		obj = make_shared<Light>(objName, centerPos, lightIndex);

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



void ObjectSpawner::DeleteObj(shared_ptr<class MapInfo> map, int index)
{
	vector<shared_ptr<Tile>>& tiles = map->GetInfos();
	Vector2 objSize = _deployTable[tiles[index]->GetObjName()]->GetSize();
	Vector2 mapSize = map->GetSize();

	int maxSize = mapSize.x * mapSize.y;

	for (int i = 0; i < objSize.y; i++)
	{
		for (int j = 0; j < objSize.x; j++)
		{
			int curIndex = index + j + i * mapSize.x;

			if (curIndex < maxSize)
				tiles[curIndex]->DeleteObj();
		}
	}

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
					_player.lock()->AddItem(dropItem->_itemName);
					dropItem->_isActive = false;
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

void ObjectSpawner::ActiveDropItem(string name, Vector2 pos)
{

	vector<DropInfo::Data> dropDatas = DATA->GetDropInfo(name)->GetDatas();

	for (int i = 0; i < dropDatas.size(); i++)
	{
		int random = rand() % 100 + 1;

		if (dropDatas[i]._percent >= random)
		{
			for (int j = 0; j < _dropItems.size(); j++)
			{
				if (!_dropItems[j]->IsActive())
				{
					_dropItems[j]->Spawn(dropDatas[i]._name, dropDatas[i]._name, pos);
					break;
				}
			}
		}
	}
}
