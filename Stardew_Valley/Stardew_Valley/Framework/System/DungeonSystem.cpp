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

	_doorCollider->Block(_player.lock()->GetCollider());

	if (_player.lock()->GetCollider()->IsCollision(_doorCollider))
	{
		if (KEY_DOWN(VK_RBUTTON))
			NextStage();
	}
}

void DungeonSystem::NextStage()
{
	int dungeonIndex = rand() % 3 + 3;

	if (dungeonIndex >= _map.lock()->GetMapInfos().size())
		dungeonIndex = 3;

	if (dungeonIndex == 3)
		_player.lock()->GetCollider()->SetPos(Vector2(400, 730));
	else if (dungeonIndex == 4)
		_player.lock()->GetCollider()->SetPos(Vector2(420, 700));
	else
		_player.lock()->GetCollider()->SetPos(Vector2(630, 1090));

	_map.lock()->ChangeMap(dungeonIndex);

	_active = true;
	_doorSpawned = false;
	_breakCount = 0;

	auto infos = _map.lock()->GetcurrentMapInfo()->GetInfos();
	for (int i = 0; i < infos.size(); i++)
	{
		if (infos[i]->GetObj() == nullptr)
			continue;
		short type = DATA->GetDeployInfo(infos[i]->GetObj()->GetName())->GetType();

		if (type == DeployableObject::Type::WALL)
			continue;
		if (type == DeployableObject::Type::DOOR)
			continue;
		if (type == DeployableObject::Type::LIGHT)
		{
			auto light = dynamic_pointer_cast<Light>(infos[i]->GetObj());
			LightManager::GetInstance()->DisableLight(light->_lightIndex);
		}
		infos[i]->DeleteObj();
	}

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
