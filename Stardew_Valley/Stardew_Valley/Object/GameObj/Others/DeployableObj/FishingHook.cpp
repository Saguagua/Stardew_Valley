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
	renderer->ChangePicture("Potato", 0);
	renderer->Render();
}

void FishingHook::Update()
{
	if (!_isActive)
		return;

	if (_timeCount <= _timeMax)
	{
		_timeCount += DELTA_TIME;
		CalculateProjectile();
	}
}

void FishingHook::SetActive(Vector2 originPos, Vector2 targetPos, Vector2 dir, float power, float angle)
{
	_isActive = true;

	_transform->SetPos(originPos);
	_transform->Update();

	_originPos = originPos;
	_targetPos = targetPos;

	_dir = dir;
	_timeCount = 0;
	_timeMax = 1;

	float timeToGround = 1.0f;
	float horizontalDistance = targetPos.x - originPos.x;
	_power = horizontalDistance / timeToGround;
	_angle = atan((_power * timeToGround) / (GRAVITY * timeToGround * timeToGround * 0.5f));

	_horizontalVelocity = _power * cos(_angle);
	_verticalVelocity = _power * sin(_angle);

	/*_power = (targetPos.x - originPos.x) / cos(_angle) + GRAVITY / (2 * sin(_angle));
	_horizontalVelocity = _power * cos(_angle);
	_verticalVelocity = _power * sin(_angle);*/
}

void FishingHook::CalculateProjectile()
{
	Vector2 pos;

	if (_dir.x != 0)
	{
		pos.x = _originPos.x + _horizontalVelocity * _timeCount;
		pos.y = _originPos.y + _verticalVelocity * _timeCount - 0.5f * _timeCount * _timeCount * GRAVITY;
	}
	else
	{
		pos.x = _originPos.x + _horizontalVelocity * _timeCount;
		pos.y = _originPos.y + _verticalVelocity * _timeCount - 0.5f * _timeCount * _timeCount * GRAVITY;
	}

	_transform->SetPos(pos);
	_transform->Update();
}