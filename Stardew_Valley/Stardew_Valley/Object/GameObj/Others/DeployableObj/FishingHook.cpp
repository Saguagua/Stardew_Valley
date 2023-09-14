#include "framework.h"
#include "FishingHook.h"

FishingHook::FishingHook()
{
	_transform = make_shared<Transform>();
	_renderer = make_shared<Sprite>("BLANK", Vector2(20, 20), SpriteType::OBJECT);
	
	vector<Vector2> indices;
	indices.push_back(Vector2(0,0));
	indices.push_back(Vector2(1,0));

	_action = make_shared<Action>(indices, Action::LOOP, 0.2f);
}

void FishingHook::Render()
{
	if (!_isActive)
		return;

	_transform->Set_World();

	if (_reversing)
		_renderer->SetImage(_resultName, 0);
	else
		_renderer->SetImage(_name, _action->GetCurFrame().x);
	
	_renderer->Render();
}

void FishingHook::Update()
{
	if (!_isActive)
		return;
	if (!_reversing)
	{
		if (_timeCount < _timeMax)
		{
			_timeCount += DELTA_TIME;
			CalculateProjectile();

			if (_timeCount >= _timeMax)
			{
				_timeCount = _timeMax;
				_name = "Bait";
				_isFlying = false;
				FishingSystem::GetInstance()->EndThrowing();
			}
		}
		else
			_action->Update();
	}
	else
	{
		if (_timeCount > 0)
		{
			_timeCount -= DELTA_TIME;
			CalculateProjectile();

			if (_timeCount <= 0)
			{
				_isActive = false;
				FishingSystem::GetInstance()->EndFishing(_resultName);
			}
			
		}
	}
}

void FishingHook::Spawn()
{
	_isActive = true;
	_reversing = false;
	_action->Reset();
	_action->Play();

	_resultName = "BLANK";
	_name = "Cherry";

	_transform->Update();
	_originPos = _transform->GetWorldPos();

	_timeCount = 0;

	if (_dir.x != 0)
	{
		_horizontalVelocity = _power * cos(_angle);
		_verticalVelocity = _power * sin(_angle);
		_timeMax = (2 * _verticalVelocity) / (GRAVITY * 100); // ¶¥¿¡ ´ê´Â ½Ã°£
	}
	else
	{
		_horizontalVelocity = _power * sin(_angle);
		_verticalVelocity = _power * cos(_angle);
		_timeMax = (2 * _horizontalVelocity) / (GRAVITY * 100);
	}
}

void FishingHook::CalculateProjectile()
{
	Vector2 pos;

	if (_dir.x != 0)
	{
		pos.x = _originPos.x + (_horizontalVelocity * _timeCount) * _dir.x;
		pos.y = _originPos.y + _verticalVelocity * _timeCount - 0.5 * GRAVITY * 100 * _timeCount * _timeCount;
	}
	else
	{
		pos.y = _originPos.y + (_verticalVelocity * _timeCount * _dir.y);
		pos.x = _originPos.x + _horizontalVelocity * _timeCount - 0.5 * GRAVITY * 100 * _timeCount * _timeCount;
	}
	_transform->SetPos(pos);
	_transform->Update();
}
