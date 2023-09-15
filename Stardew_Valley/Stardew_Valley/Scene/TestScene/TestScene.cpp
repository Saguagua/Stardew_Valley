#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	DATA->LoadPlayerInfo("Test");
	FishingSystem::Create();
	DungeonSystem::Create();
	MonsterSpawner::Create();
	
	EffectManager::Create();

	_player = make_shared<PlayerImproved>();
	_player->Initialize();
	_player->GetTransform()->SetPos(CENTER);
	PlayerUI::Create(_player);
	OBJECT_SPAWNER->SetPlayer(_player);

	DATA->LoadMaps("Test");
	_map = make_shared<TileMap>(DATA->GetPlayerMapInfos());
	_map->ChangeMap(0);

	_player->SetMap(_map);

	FishingSystem::GetInstance()->SetPlayer(_player);
	FishingSystem::GetInstance()->SetMap(_map);
	
	DungeonSystem::GetInstance()->SetPlayer(_player);
	DungeonSystem::GetInstance()->SetMap(_map);


	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->Update();

	MONSTER_SPAWNER->SetPlayer(_player);
	MONSTER_SPAWNER->SetTileMap(_map);
	SOUND->Add("bgm1", "Resource/Sound/bgm1.mp3", true);
	SOUND->Play("bgm1");

	_cover = make_shared<FrontCover>();
	CallBack cb = std::bind(&TestScene::ChangeMap, this);
	_cover->SetCallBack(cb);
}

TestScene::~TestScene()
{
	MonsterSpawner::Delete();
	FishingSystem::Delete();
	PlayerUI::Delete();
	DungeonSystem::Delete();
	EffectManager::Delete();
}

void TestScene::Update()
{
	PLAYERUI->Update();
	_player->Update();
	FishingSystem::GetInstance()->Update();

	_map->Blocking(_player->GetCollider());

	

	MONSTER_SPAWNER->Update();
	DungeonSystem::GetInstance()->Update();
	EFFECT->Update();

	if (!CAMERA->_freeMode && !SCENEMANAGER->_changeScene)
	{
		KeyInput();

		for (int i = 0; i < _map->_teleports.size(); i++)
		{
			if (_player->GetCollider()->IsCollision(_map->_teleports[i]->_collider))
			{
				_teleportInfo = _map->_teleports[i];
				SCENEMANAGER->_changeScene = true;
			}
		}
	}
	else if (SCENEMANAGER->_changeScene)
	{
		_cover->Update();
	}
}

void TestScene::Render()
{
	_map->Render();
	_player->Render();
	FishingSystem::GetInstance()->Render();
	DungeonSystem::GetInstance()->Render();
	MONSTER_SPAWNER->Render();
	EFFECT->Render();
}

void TestScene::PostRender()
{
	_player->PostRender();
	PLAYERUI->PostRender();
	EFFECT->PostRender();

	if (SCENEMANAGER->_changeScene)
	{
		_cover->PostRender();
	}
}

void TestScene::KeyInput()
{
	if (!PLAYERUI->GetBagMode())
	{
		_player->KeyInput();

		_map->GetFocusedTile(_player->GetCollider()->GetWorldPos(), W_MOUSE_POS)->Interaction();
	}
}

void TestScene::ChangeMap()
{
	Vector2 pos = _teleportInfo->_where;
	_map->ChangeMap(_teleportInfo->_destination);
	_player->GetTransform()->SetPos(pos);
	_player->SetIdle();
}

void TestScene::Initialize()
{
	CAMERA->_freeMode = false;
	CAMERA->SetPos(_player->GetWorldPos());
	CAMERA->Update();
}
