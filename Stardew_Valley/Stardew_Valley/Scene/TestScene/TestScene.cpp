#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	ObjectSpawner::Create();
	DATA->LoadPlayerInfo("Test");
	LightManager::Create();

	FishingSystem::Create();
	
	_player = make_shared<PlayerImproved>();
	PlayerUI::Create(_player);
	OBJECT_SPAWNER->SetPlayer(_player);

	DATA->LoadMaps("Test");
	_map = make_shared<TileMap>();
	_items = _player->GetItems();

	FishingSystem::GetInstance()->SetPlayer(_player);
	FishingSystem::GetInstance()->SetMap(_map);

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->Update();
}

TestScene::~TestScene()
{
	LightManager::Delete();
	ObjectSpawner::Delete();
	FishingSystem::Delete();
	PlayerUI::Delete();
}

void TestScene::Update()
{
	LightManager::GetInstance()->Update();
	OBJECT_SPAWNER->Update();
	PLAYERUI->Update();
	_map->Update();
	_player->Update();
	FishingSystem::GetInstance()->Update();

	_map->Blocking(_player->GetCollider());
	
	KeyInput();
}

void TestScene::Render()
{
	_map->Render();
	OBJECT_SPAWNER->Render();
	_player->Render();
	FishingSystem::GetInstance()->Render();
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
