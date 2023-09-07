#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	DATA->LoadPlayerInfo("Test");
	FishingSystem::Create();
	MonsterSpawner::Create();
	
	_player = make_shared<PlayerFight>();
	_player->GetTransform()->SetPos(CENTER);
	PlayerUI::Create(_player);
	OBJECT_SPAWNER->SetPlayer(_player);

	DATA->LoadMaps("Test");
	_map = make_shared<TileMap>(DATA->GetPlayerMapInfos());
	_map->ChangeMap(0);
	_items = _player->GetItems();

	FishingSystem::GetInstance()->SetPlayer(_player);
	FishingSystem::GetInstance()->SetMap(_map);

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->Update();

	MONSTER_SPAWNER->SetPlayer(_player);
	MONSTER_SPAWNER->SetTileMap(_map);

	MONSTER_SPAWNER->Spawn(10);
}

TestScene::~TestScene()
{
	MonsterSpawner::Delete();
	FishingSystem::Delete();
	PlayerUI::Delete();
}

void TestScene::Update()
{
	PLAYERUI->Update();
	_player->Update();
	FishingSystem::GetInstance()->Update();

	_map->Blocking(_player->GetCollider());


	MONSTER_SPAWNER->Update();

	KeyInput();
}

void TestScene::Render()
{
	_map->Render();
	_player->Render();
	FishingSystem::GetInstance()->Render();

	MONSTER_SPAWNER->Render();
}

void TestScene::PostRender()
{
	PLAYERUI->PostRender();
}

void TestScene::KeyInput()
{
	if (!PLAYERUI->GetBagMode())
	{
		_player->KeyInput();


		shared_ptr<Item> item = _items[_player->GetCurIndex()];
		int type = item->GetType();

		switch (type)
		{
		case Item::EATABLE:
		{
			item->Eat(_player);
			break;
		}
		case Item::FISHINGROD:
		{
			item->Fishing(_player);
			break;
		}
		case Item::HOE:
		{
			item->Hoe(_player, _map);
			break;
		}
		case Item::AXE:
		case Item::PICKAXE:
		{
			item->Break(_player, _map);
			break;
		}
		case Item::WATERINGCAN:
		{
			item->Water(_player, _map);
			break;
		}
		case Item::SEED:
		{
			item->Seed(_player, _map);
			break;
		}
		case Item::FERTILIZER:
		{
			item->Fertilizer(_player, _map);
			break;
		}
		case Item::WEAPON:
		{
			item->Weapon(_player);
			break;
		}
		case Item::FACILITY:
			break;
		default:
		{
			_map->GetFocusedTile(_player->GetCollider()->GetWorldPos(), W_MOUSE_POS)->Interaction();
		}
		break;
		}
	}
}

void TestScene::Initialize()
{
}
