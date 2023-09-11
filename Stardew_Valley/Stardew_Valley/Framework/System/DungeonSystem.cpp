#include "framework.h"
#include "DungeonSystem.h"

DungeonSystem* DungeonSystem::_instance = nullptr;

DungeonSystem::DungeonSystem()
{
	_renderer = make_shared<Sprite>("DungeonGate", TILE_SIZE, SpriteType::OBJECT);
	_doorCollider = make_shared<RectCollider>(TILE_SIZE);
}

void DungeonSystem::Render()
{
	if (!_doorSpawned)
		return;

	_doorCollider->GetTransform()->Set_World();
	_renderer->Render();
	_doorCollider->Render();
}

void DungeonSystem::Update()
{
	if (!_doorSpawned)
		return;

	_doorCollider->Update();

	if (_player.lock()->GetCollider()->IsCollision(_doorCollider))
	{
		NextStage();
	}
}

void DungeonSystem::NextStage()
{
	_active = true;
	_doorSpawned = false;

	int dungeonIndex = rand() % 3 + 3;

	_map.lock()->ChangeMap(dungeonIndex);
	OBJECT_SPAWNER->SpawnObjects(_map.lock());
	MONSTER_SPAWNER->Initialize();
}

void DungeonSystem::SpawnDoor(Vector2 pos)
{
	if (!_active || _doorSpawned)
		return;

	_breakCount++;

	int randomInt = rand() % 100;

	if (randomInt > _defaultPercent + _breakCount * 5)
		return;

	_doorCollider->SetPos(pos);
	_doorSpawned = true;
}
