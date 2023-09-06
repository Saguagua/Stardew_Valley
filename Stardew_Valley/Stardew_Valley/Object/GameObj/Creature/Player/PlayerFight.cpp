#include "framework.h"
#include "PlayerFight.h"


PlayerFight::PlayerFight()
	:PlayerImproved()
{
	_weaponSlot = make_shared<Transform>();

	_weaponSlot->SetParent(_col->GetTransform());

	_weaponCollider = make_shared<RectCollider>(Vector2(20,40));
	_weaponCollider->SetPos(Vector2(0.0f, -10.0f));

	_weaponCollider->SetDebug(true);
	_weaponCollider->SetAngle(XM_PI);
	_weaponCollider->SetParent(_weaponSlot);
}

void PlayerFight::Render()
{
	PlayerImproved::Render();
	_weaponCollider->Render();
	_obj->ChangePicture("Sword");
	_obj->Render();
}

void PlayerFight::Update()
{
	PlayerImproved::Update();


	if (KEY_DOWN(VK_LBUTTON))
	{
		if (!_isAttacking)
		{
			if (_direction == FRONT)
				_weaponSlot->SetAngle(XM_PIDIV2);
			
			else if (_direction == SIDE)
				_weaponSlot->SetAngle(XM_PI);
			
			else if (_direction == BACK)
				_weaponSlot->SetAngle(-XM_PIDIV2);
			
			_attackCount = 0.0f;
			_isAttacking = true;
		}

	}

	if (_isAttacking)
	{
		_attackCount += DELTA_TIME;
		_weaponSlot->AddAngle(-1 * DELTA_TIME * 10.0f);
		if (_attackCount > 0.25f)
			_isAttacking = false;
	}

	_weaponSlot->Update();
	_weaponCollider->Update();
}

void PlayerFight::AddMaxHP(short cost)
{
}

void PlayerFight::AddMaxStamina(short cost)
{
}

void PlayerFight::AddHP(short cost)
{
	_hp += cost;

	if (_hp <= 0)
		_state = (PlayerState::DEAD);

	float ratio = (float)_hp / (float)_maxHp;
	PlayerUI::GetInstance()->SetHP(ratio);
}

void PlayerFight::AddStamina(short cost)
{
	_stamina += cost;

	if (_stamina <= 0)
		_state = (PlayerState::DEAD);

	float ratio = _stamina / _maxHp;
	PlayerUI::GetInstance()->SetStamina(ratio);
}
