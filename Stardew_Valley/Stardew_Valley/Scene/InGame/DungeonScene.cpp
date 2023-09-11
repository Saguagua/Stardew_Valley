#include "framework.h"
#include "DungeonScene.h"

DungeonScene::DungeonScene(shared_ptr<PlayerFight> p)
	:_player(p)
{
	_mapCount = DATA->GetDungeonMapInfos().size();

	_map = make_shared<TileMap>(DATA->GetDungeonMapInfos());

	_items = _player.lock()->GetItems();

	MonsterSpawner::Create();
	MONSTER_SPAWNER->SetPlayer(_player.lock());
	MONSTER_SPAWNER->SetTileMap(_map);
}

DungeonScene::~DungeonScene()
{
	MonsterSpawner::Delete();
}

void DungeonScene::Update()
{
	if (!_player.expired())
	{
		_player.lock()->Update();
		KeyInput();
		_map->Blocking(_player.lock()->GetCollider());
	}

	MONSTER_SPAWNER->Update();
}

void DungeonScene::Render()
{
	if (!_player.expired())
		_player.lock()->Render();

	MONSTER_SPAWNER->Render();
}

void DungeonScene::Initialize()
{
	_stair = 1;
	int randomInt = rand() % _mapCount;
	_map->ChangeMap(randomInt);
	int randomMonsterCount = rand() % 10;
	MONSTER_SPAWNER->Spawn(10);
}

void DungeonScene::KeyInput()
{
	if (!PLAYERUI->GetBagMode())
	{
		_player.lock()->KeyInput();


		shared_ptr<Item> item = _items[_player.lock()->GetCurIndex()];
		int type = item->GetType();

		switch (type)
		{
		case Item::EATABLE:
		{
			item->Eat(_player.lock());
			break;
		}
		case Item::FISHINGROD:
		{
			item->Fishing(_player.lock());
			break;
		}
		case Item::HOE:
		{
			item->Hoe(_player.lock(), _map);
			break;
		}
		case Item::AXE:
		case Item::PICKAXE:
		{
			item->Break(_player.lock(), _map);
			break;
		}
		case Item::WATERINGCAN:
		{
			item->Water(_player.lock(), _map);
			break;
		}
		case Item::SEED:
		{
			item->Seed(_player.lock(), _map);
			break;
		}
		case Item::FERTILIZER:
		{
			item->Fertilizer(_player.lock(), _map);
			break;
		}
		case Item::WEAPON:
		{
			item->Weapon(_player.lock());
			break;
		}
		case Item::FACILITY:
			break;
		default:
		{
			_map->GetFocusedTile(_player.lock()->GetCollider()->GetWorldPos(), W_MOUSE_POS)->Interaction();
		}
		break;
		}
	}
}
