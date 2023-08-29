#include "framework.h"
#include "FishingHook.h"

FishingHook::FishingHook()
{
	_transform = make_shared<Transform>();
	_renderer = make_shared<Sprite>(XMLPATH, "BLANK", Vector2(20, 20), SpriteType::OBJECT);
}

void FishingHook::Render()
{
	if (!_isActive)
		return;

	_transform->Set_World();
	_renderer->ChangePicture(_name, 0);
	_renderer->Render();
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
			_isFlying = false;
			FishingSystem::GetInstance()->CheckTile();
		}
	}
}

void FishingHook::Spawn(Vector2 dir, float power)
{
	_isActive = true;
	_dir = dir;
	_transform->Update();
	_originPos = _transform->GetWorldPos();
	_timeCount = 0;
	_power = power; // �ʱ� �ӵ� 700 ~ 300
	_angle = 60.0 * 3.141592 / 180.0; // ���� (�� ����)
	_name = "Potato";

	if (_dir.x != 0)
	{
		_horizontalVelocity = _power * cos(_angle);
		_verticalVelocity = _power * sin(_angle);
		_timeMax = (2 * _verticalVelocity) / (GRAVITY * 100); // ���� ��� �ð�
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
