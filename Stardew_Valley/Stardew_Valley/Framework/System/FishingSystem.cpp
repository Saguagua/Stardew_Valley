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
		_hook->Update();

		_waitCount += DELTA_TIME;

		if (_waitCount >= 1.0f)
		{
			_waitCount = 0.0f;

			int random = rand() % 100;

			if (random > 50)
			{
				_fishName = "Anchovy";
				_step = Step::HOLD;
				_minigame->SetActive(true);
				_minigame->Update();
				_player.lock()->PlayAction(Player::PlayerAction::FISHING2);
			}
		}
		break;
	}
	case FishingSystem::HOLD:
	{
		_hook->Update();
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

void FishingSystem::HookSetting(Vector2 direction, float power)
{
	_hook->SetDirection(direction);
	_hook->SetPower(power);

	if (!_player.expired())
		_hook->SetPos(_player.lock()->GetWorldPos());
}

void FishingSystem::ActiveFishingHook()
{
	_hook->Spawn();
	_player.lock()->SetFreeze(true);
}

void FishingSystem::EndThrowing()
{
	auto tile = _map.lock()->GetWorldTile(_hook->GetWorldPos());

	if (!(DATA->GetTileInfo(tile->GetName()) & TileType::FISHING))
	{
		_hook->SetActive(false);
		_player.lock()->SetFreeze(false);
	}
	else
	{
		_step = Step::WAIT;
		_waitCount = 0.0f;
	}
}

void FishingSystem::EndMinigame(bool result)
{
	_step = Step::CATCH;

	_minigame->SetActive(false);
	_hook->SetReverse(true);

	if (result)
		_hook->SetResultName(_fishName);
	else
		_hook->SetResultName("BLANK");
	
}

void FishingSystem::EndFishing(string itemName)
{
	_step = Step::THROW;

	if (itemName != "BLANK")
		_player.lock()->AddItem(itemName);

	_player.lock()->PlayAction(Player::PlayerAction::FISHING3);
}
