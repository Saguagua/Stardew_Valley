#include "framework.h"
#include "FishingHook.h"

FishingHook::FishingHook()
{
	_transform = make_shared<Transform>();
}

void FishingHook::Render(shared_ptr<Sprite> renderer)
{
	if (!_isActive)
		return;

	_transform->Set_World();
	renderer->ChangePicture(_name, 0);
	renderer->Render();
}

void FishingHook::Update()
{
	if (!_isActive)
		return;

	if (_timeCount < _timeMax)
	{
		_timeCount += DELTA_TIME;
		CalculateProjectile();

		if (_timeCount >= _timeMax)
		{
			_name = "Bait";
			_isLand = true;
		}
			
	}
}

void FishingHook::SetActive(Vector2 originPos, Vector2 dir, float power)
{
	_isActive = true;
	_isLand = false;
	_dir = dir;
	_originPos = originPos;
	_transform->SetPos(originPos);
	_transform->Update();
	_timeCount = 0;
	_power = power; // 초기 속도 700 ~ 300
	_angle = 60.0 * 3.141592 / 180.0; // 각도 (도 단위)
	_name = "Potato";

	if (_dir.x != 0)
	{
		_horizontalVelocity = _power * cos(_angle);
		_verticalVelocity = _power * sin(_angle);
		_timeMax = (2 * _verticalVelocity) / (GRAVITY * 100); // 땅에 닿는 시간
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
