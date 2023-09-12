#include "framework.h"
#include "MonsterSpawner.h"
#include "Object/UI/NumberUI.h"
MonsterSpawner* MonsterSpawner::_instance = nullptr;

MonsterSpawner::MonsterSpawner()
{
	for (int i = 0; i < 10; i++)
	{
		_monsters.push_back(make_shared<Slime>());
	}
	for (int i = 0; i < 10; i++)
	{
		_monsters.push_back(make_shared<Bat>());
	}
}

void MonsterSpawner::Update()
{
	for (shared_ptr<Monster> monster : _monsters)
	{
		if (!monster->IsActive())
			continue;

		monster->Update();

		if (!_map.expired() && monster->_type == Monster::MoveType::WALK)
			_map.lock()->Blocking(monster->GetCollider());

		if (!_player.expired())
		{
			if (_player.lock()->_isAttacking)
			{
				if (_player.lock()->_weaponCollider->OBB(monster->GetCollider()) && !monster->IsUntouchable())
				{
					Vector2 dir = (monster->GetWorldPos() - _player.lock()->GetWorldPos()).Normalize();
					monster->AddPos(dir * 10);
					monster->AddHP(-2);
					monster->StartUntouchable(0.5f);
					EFFECT->ActiveDamage(2, monster->GetWorldPos());
				}
			}

			monster->Detect(_player.lock());
		}
	}
}

void MonsterSpawner::Render()
{
	for (shared_ptr<Monster> monster : _monsters)
	{
		if (!monster->IsActive())
			continue;

		monster->Render();
	}
}

void MonsterSpawner::PostRender()
{
}

void MonsterSpawner::Spawn(int count)
{
	int slimeMax = rand() % count;
	int monsterCount = 0;
	int tileIndex = 0;
	vector<shared_ptr<Tile>> tiles = _map.lock()->GetcurrentMapInfo()->GetInfos();

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(tiles.begin(), tiles.end(), g);

	for (int i = 0; i < 10; i++)
	{
		if (monsterCount >= slimeMax)
			break;

		if (!_monsters[i]->IsActive())
		{
			for (; tileIndex < tiles.size(); tileIndex++)
			{
				if ((tiles[tileIndex]->GetObj() == nullptr) && 
					!(DATA->GetTileInfo(tiles[tileIndex]->GetName()) & TileType::BLOCK))
				{
					_monsters[i]->Spawn(tiles[tileIndex]->GetCenterPos());
					monsterCount++;
					tileIndex++;
					break;
				}
			}
		}
	}

	for (int i = 10; i < 20; i++)
	{
		if (monsterCount >= count)
			break;

		if (!_monsters[i]->IsActive())
		{
			for (; tileIndex < tiles.size(); tileIndex++)
			{
				if (tiles[tileIndex]->GetObj() == nullptr)
				{
					_monsters[i]->Spawn(tiles[tileIndex]->GetCenterPos());
					monsterCount++;
					tileIndex++;
					break;
				}
			}
		}
	}
	
}

void MonsterSpawner::Initialize()
{
	for (int i = 0; i < _monsters.size(); i++)
	{
		_monsters[i]->SetActive(false);
	}

	int randomInt = rand() % 10 + 1;

	Spawn(randomInt);
}
