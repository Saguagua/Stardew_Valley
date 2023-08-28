#include "framework.h"
#include "TestScene.h"


TestScene::TestScene()
{
	ObjectSpawner::Create();
	DATA->LoadPlayerInfo("Test");
	LightManager::Create();
	
	_player = make_shared<PlayerImproved>();
	PlayerUI::Create(_player);
	OBJECT_SPAWNER->SetPlayer(_player);

	DATA->LoadMaps("Test");
	_map = make_shared<TileMap>();
	_items = _player->GetItems();

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->Update();
}

TestScene::~TestScene()
{
	LightManager::Delete();
	ObjectSpawner::Delete();
}

void TestScene::Update()
{
	LightManager::GetInstance()->Update();
	OBJECT_SPAWNER->Update();
	PLAYERUI->Update();
	_player->Update();
	_map->Update();

	_map->Blocking(_player->GetCollider());
	if (_player->IsHookLanded())
	{
		if (_map->CanFishing(_player->GetHookPos()))
		{
			_player->SetFishing(true);
		}
	}
	
	KeyInput();
}

void TestScene::Render()
{
	_map->Render();
	OBJECT_SPAWNER->Render();
	_player->Render();
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

		if (KEY_DOWN('1'))
		{
			_player->SetCurItem(0);
		}
		else if (KEY_DOWN('2'))
		{
			_player->SetCurItem(1);
		}
		else if (KEY_DOWN('3'))
		{
			_player->SetCurItem(2);
		}
		else if (KEY_DOWN('4'))
		{
			_player->SetCurItem(3);
		}
		else if (KEY_DOWN('5'))
		{
			_player->SetCurItem(4);
		}
		else if (KEY_DOWN('6'))
		{
			_player->SetCurItem(5);
		}
		else if (KEY_DOWN('7'))
		{
			_player->SetCurItem(6);
		}
		else if (KEY_DOWN('8'))
		{
			_player->SetCurItem(7);
		}
		else if (KEY_DOWN('9'))
		{
			_player->SetCurItem(8);
		}
		else if (KEY_DOWN('0'))
		{
			_player->SetCurItem(9);
		}

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
