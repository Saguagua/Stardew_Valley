#include "framework.h"
#include "DungeonSystem.h"

DungeonSystem* DungeonSystem::_instance = nullptr;

DungeonSystem::DungeonSystem()
{
	_renderer = make_shared<Sprite>("DungeonGate", TILE_SIZE, SpriteType::OBJECT);
	_doorCollider = make_shared<RectCollider>(TILE_SIZE);
	_cb = std::bind(&DungeonSystem::NextStage, this);
}

void DungeonSystem::Render()
{
	if (!_isActive)
		return;
	if (!_doorSpawned)
		return;

	_doorCollider->GetTransform()->Set_World();
	_renderer->Render();
	_doorCollider->Render();
}

void DungeonSystem::Update()
{
	if (!_isActive)
		return; 
	if (!_doorSpawned)
		return;

	_doorCollider->Update();

	_doorCollider->Block(_player.lock()->GetCollider());

	if (_player.lock()->GetCollider()->IsCollision(_doorCollider))
	{
		if (KEY_DOWN(VK_RBUTTON))
		{
			SCENEMANAGER->_cover->FadeStart(_cb, nullptr);
		}
	}
}

void DungeonSystem::NextStage()
{
	int dungeonIndex = rand() % 3 + 4;

	if (dungeonIndex >= _map.lock()->GetMapInfos().size())
		dungeonIndex = 4;

	if (dungeonIndex == 4)
		_player.lock()->GetCollider()->SetPos(Vector2(410, 750));
	else if (dungeonIndex ==  5)
		_player.lock()->GetCollider()->SetPos(Vector2(550, 1100));
	else
		_player.lock()->GetCollider()->SetPos(Vector2(390, 1490));

	_map.lock()->ChangeMap(dungeonIndex);

	_isActive = true;
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
		if (type == DeployableObject::Type::ELEVATOR)
			continue;

		if (type == DeployableObject::Type::LIGHT)
		{
			auto light = dynamic_pointer_cast<Light>(infos[i]->GetObj());
			LightManager::GetInstance()->DisableLight(light->_lightIndex);
		}
		infos[i]->DeleteObj();
	}

	int objCount = rand() % 5 + 19;

	OBJECT_SPAWNER->SpawnObjects(_map.lock(), dungeonIndex, objCount);
	MONSTER_SPAWNER->Initialize();
}

void DungeonSystem::SpawnDoor(Vector2 pos)
{
	if (!_isActive || _doorSpawned)
		return;

	_breakCount++;

	int randomInt = rand() % 100;

	if (randomInt > _defaultPercent + _breakCount * 5)
		return;

	_doorCollider->SetPos(pos);
	_doorSpawned = true;
}

void DungeonSystem::Return()
{
	_map.lock()->ChangeMap(2);
	_player.lock()->GetCollider()->SetPos(Vector2(376, 743));
	MONSTER_SPAWNER->DiableAll();
	_isActive = false;
}
