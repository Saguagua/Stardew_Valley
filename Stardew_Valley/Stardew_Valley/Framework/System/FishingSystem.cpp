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
			
			int random = rand() % 100;

			UINT size = _fishInfos[_dayNightIndex]->_size;
			_waitCount = 0.0f;
			
			for (int i = 0; i < size; i++)
			{
				if (random < _fishInfos[_dayNightIndex]->_percents[i])
				{
					_waitCount = 1.0f;
					_fishName = _fishInfos[_dayNightIndex]->_fishNames[i];
					_step = Step::CLICK;
					EFFECT->ActiveEffect(_hook->GetWorldPos(), 2);
					break;
				}
			}
		}

		break;
	}
	case FishingSystem::CLICK:
	{
		_waitCount -= DELTA_TIME;

		if (_waitCount <= 0)
		{
			EndMinigame(false);
		}

		if (KEY_DOWN(VK_LBUTTON))
		{
			_step = Step::HOLD;
			_minigame->SetActive(true);
			_minigame->Update();
			_player.lock()->PlayAction(Player::PlayerAction::FISHING2);
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
		_player.lock()->SetToolActive(false);
		_player.lock()->PlayAction(Player::PlayerAction::IDLE);

	}
	else
	{
		_step = Step::WAIT;
		_waitCount = 0.0f;
		_dayNightIndex = TIMER->GetDayTime();
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
	_player.lock()->SetToolActive(false);

	if (itemName != "BLANK")
		_player.lock()->AddItem(itemName);

	_player.lock()->PlayAction(Player::PlayerAction::FISHING3);
}
