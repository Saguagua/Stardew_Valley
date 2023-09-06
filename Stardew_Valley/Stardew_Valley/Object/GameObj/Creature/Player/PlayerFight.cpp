#include "framework.h"
#include "PlayerFight.h"


PlayerFight::PlayerFight()
	:PlayerImproved()
{
	_weaponSlot = make_shared<Transform>();

	_weaponSlot->SetParent(_col->GetTransform());

	_weaponCollider = make_shared<RectCollider>(Vector2(20,40));

	_weaponCollider->SetPos(Vector2(0.0f, -20.0f));
	_weaponCollider->SetDebug(true);
	_weaponCollider->SetAngle(XM_PI);
	_weaponCollider->SetParent(_weaponSlot);

	_weaponRotate = make_shared<Transform>();
	_weaponRotate->SetParent(_weaponCollider->GetTransform());
	_weaponRotate->SetAngle(45.0f * XM_PI / 180.0f);

	_weapon = make_shared<Sprite>(XMLPATH1, "BLANK", Vector2(30, 30), SpriteType::OBJECT);
}

void PlayerFight::Render()
{
	PlayerImproved::Render();
	_weaponRotate->Set_World();

	if (_isAttacking)
	{
		_weapon->ChangePicture("Sword");
		_weapon->Render();
		_weaponCollider->Render();
	}
}

void PlayerFight::Update()
{
	PlayerImproved::Update();


	if (_isAttacking)
	{
		_attackCount += DELTA_TIME;
		_weaponSlot->AddAngle(-1 * DELTA_TIME * 10.0f);

		if (_attackCount > 0.25f)
			_isAttacking = false;
	}

	_weaponSlot->Update();
	_weaponCollider->Update();
	_weaponRotate->Update();
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
