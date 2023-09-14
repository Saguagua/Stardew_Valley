#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	DATA->LoadPlayerInfo("Test");
	FishingSystem::Create();
	DungeonSystem::Create();
	MonsterSpawner::Create();
	
	EffectManager::Create();

	_player = make_shared<PlayerFight>();
	_player->Initialize();//Fight를 부모로 바꿀듯?
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

	for (int i = 0; i < _map->_teleports.size(); i++)
	{
		if (_player->GetCollider()->IsCollision(_map->_teleports[i]->_collider))
		{
			Vector2 pos = _map->_teleports[i]->_where;
			_map->ChangeMap(_map->_teleports[i]->_destination);
			_player->GetTransform()->SetPos(pos);
		}
	}

	MONSTER_SPAWNER->Update();
	DungeonSystem::GetInstance()->Update();
	EFFECT->Update();

	if (!CAMERA->_freeMode)
		KeyInput();
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
}

void TestScene::KeyInput()
{
	if (!PLAYERUI->GetBagMode())
	{
		_player->KeyInput();

		_map->GetFocusedTile(_player->GetCollider()->GetWorldPos(), W_MOUSE_POS)->Interaction();
	}
}

void TestScene::Initialize()
{
	CAMERA->_freeMode = false;
	CAMERA->SetPos(_player->GetWorldPos());
	CAMERA->Update();
}
