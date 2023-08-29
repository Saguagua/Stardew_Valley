#include "framework.h"
#include "FishingSystem.h"

FishingSystem* FishingSystem::_instance = nullptr;

FishingSystem::FishingSystem()
{
	_minigame = make_shared<FishingMinigame>();
	_hook = make_shared<FishingHook>();
}

void FishingSystem::Update()
{
	switch (_step)
	{
	case FishingSystem::THROW:
	{
		_hook->Update();
		break;
	}
	case FishingSystem::WAIT:
	{
		int random = rand() % 100;

		if (random > 50)
		{
			_fishName = "Anchovy";
			_step = Step::HOLD;
			_minigame->SetActive(true);
			_minigame->Update();
		}

		break;
	}
	case FishingSystem::HOLD:
	{
		_minigame->Update();
		break;
	}
	case FishingSystem::CATCH:
	{
		_hook->Update();
		break;
	}
	default:
		break;
	}
}

void FishingSystem::Render()
{
	_hook->Render();
	_minigame->Render();
}

void FishingSystem::SetPlayer(shared_ptr<PlayerImproved> player)
{
	_player = player;

	_minigame->GetTransform()->SetParent(_player.lock()->GetTransform());
	_minigame->SetPos(Vector2(-70, 100));
	_minigame->Update();
	_minigame->SetActive(false);
}

void FishingSystem::ActiveFishingHook(Vector2 direction, float power)
{
	_hook->SetPos(_player.lock()->GetWorldPos());
	
	_hook->Spawn(direction, power);
	_player.lock()->SetFreeze(true);
}

void FishingSystem::CheckTile()
{
	auto tile = _map.lock()->GetWorldTile(_hook->GetWorldPos());

	if (!(DATA->GetTileInfo(tile->GetName()) & TileType::FISHING))
		_hook->SetActive(false);
	else
		_step = Step::WAIT;

	
}

void FishingSystem::EndMinigame(string name)
{
	_step = Step::CATCH;
	_minigame->SetActive(false);
	_fishName = name;
}
