#include "framework.h"
#include "PlayerFight.h"


PlayerFight::PlayerFight()
	:PlayerImproved()
{
	_weaponSlot = make_shared<Transform>();

	_weaponSlot->SetPos(Vector2(0.0f, 10.0f));
	_weaponSlot->SetParent(_col->GetTransform());

	_weaponCollider = make_shared<RectCollider>(Vector2(20.0f, 40.0f));

	_weaponCollider->SetPos(Vector2(0.0f, -20.0f));
	_weaponCollider->SetAngle(XM_PI);
	_weaponCollider->SetParent(_weaponSlot);

	_weaponRotate = make_shared<Transform>();
	_weaponRotate->SetParent(_weaponCollider->GetTransform());
	_weaponRotate->SetAngle(45.0f * XM_PI / 180.0f);

	_weapon = make_shared<Sprite>("Sword", Vector2(30, 30), SpriteType::OBJECT);

	CreateAction();
}

void PlayerFight::Render()
{
	PlayerImproved::Render();
	_weaponRotate->Set_World();

	if (_isAttacking)
	{
		_weapon->SetImage("Sword");
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


void PlayerFight::SetIdle()
{
	Player::SetIdle();
}

void PlayerFight::CreateAction()
{
#pragma region Attack
	//FrontAttack
	{
		CallBack cb = std::bind(&PlayerFight::SetIdle, this);
		CallBackBool cbb = std::bind(&PlayerFight::SetFreeze, this, false);

		vector<Vector2> frontBody;
		frontBody.push_back(Vector2(0, 4));
		frontBody.push_back(Vector2(1, 4));
		frontBody.push_back(Vector2(2, 4));
		frontBody.push_back(Vector2(3, 4));
		frontBody.push_back(Vector2(4, 4));
		frontBody.push_back(Vector2(5, 4));

		shared_ptr<Action> FrontBody = make_shared<Action>(frontBody, Action::Type::END, 0.05f);
		FrontBody->AddEndEvent(cb);
		FrontBody->SetEndBoolEvent(cbb);

		_actions.push_back(FrontBody);

		vector<Vector2> frontArm;
		frontArm.push_back(Vector2(12, 4));
		frontArm.push_back(Vector2(13, 4));
		frontArm.push_back(Vector2(14, 4));
		frontArm.push_back(Vector2(15, 4));
		frontArm.push_back(Vector2(16, 4));
		frontArm.push_back(Vector2(17, 4));

		shared_ptr<Action> FrontArm = make_shared<Action>(frontArm, Action::Type::END, 0.05f);
		FrontArm->AddEndEvent(cb);

		_armActions.push_back(FrontArm);
	}

	//SideAttack
	{
		CallBack cb = std::bind(&PlayerFight::SetIdle, this);
		CallBackBool cbb = std::bind(&PlayerFight::SetFreeze, this, false);

		vector<Vector2> sideBody;
		sideBody.push_back(Vector2(0, 5));
		sideBody.push_back(Vector2(1, 5));
		sideBody.push_back(Vector2(2, 5));
		sideBody.push_back(Vector2(3, 5));
		sideBody.push_back(Vector2(4, 5));
		sideBody.push_back(Vector2(5, 5));

		shared_ptr<Action> SideBody = make_shared<Action>(sideBody, Action::Type::END, 0.05f);

		SideBody->AddEndEvent(cb);
		SideBody->SetEndBoolEvent(cbb);


		_actions.push_back(SideBody);

		vector<Vector2> sideArm;
		sideArm.push_back(Vector2(12, 5));
		sideArm.push_back(Vector2(13, 5));
		sideArm.push_back(Vector2(14, 5));
		sideArm.push_back(Vector2(15, 5));
		sideArm.push_back(Vector2(16, 5));
		sideArm.push_back(Vector2(17, 5));

		shared_ptr<Action> SideArm = make_shared<Action>(sideArm, Action::Type::END, 0.05f);

		SideArm->AddEndEvent(cb);

		_armActions.push_back(SideArm);
	}

	//BackAttack
	{
		CallBack cb = std::bind(&PlayerFight::SetIdle, this);
		CallBackBool cbb = std::bind(&PlayerFight::SetFreeze, this, false);

		vector<Vector2> backBody;
		backBody.push_back(Vector2(0, 6));
		backBody.push_back(Vector2(1, 6));
		backBody.push_back(Vector2(2, 6));
		backBody.push_back(Vector2(3, 6));
		backBody.push_back(Vector2(4, 6));
		backBody.push_back(Vector2(5, 6));

		shared_ptr<Action> BackBody = make_shared<Action>(backBody, Action::Type::END, 0.05f);

		BackBody->AddEndEvent(cb);
		BackBody->SetEndBoolEvent(cbb);

		_actions.push_back(BackBody);

		vector<Vector2> backArm;
		backArm.push_back(Vector2(12, 6));
		backArm.push_back(Vector2(13, 6));
		backArm.push_back(Vector2(14, 6));
		backArm.push_back(Vector2(15, 6));
		backArm.push_back(Vector2(16, 6));
		backArm.push_back(Vector2(17, 6));

		shared_ptr<Action> BackArm = make_shared<Action>(backArm, Action::Type::END, 0.05f);

		BackArm->AddEndEvent(cb);

		_armActions.push_back(BackArm);
	}
#pragma endregion


#pragma region Holding
	{
		vector<Vector2> frontHolding;
		frontHolding.push_back(Vector2(12, 0));
		frontHolding.push_back(Vector2(13, 0));
		frontHolding.push_back(Vector2(14, 0));

		shared_ptr<Action> frontHAction = make_shared<Action>(frontHolding, Action::Type::LOOP, 0.1f);

		vector<Vector2> sideHolding;
		sideHolding.push_back(Vector2(12, 1));
		sideHolding.push_back(Vector2(13, 1));
		sideHolding.push_back(Vector2(14, 1));

		shared_ptr<Action> sideHAction = make_shared<Action>(sideHolding, Action::Type::LOOP, 0.1f);

		vector<Vector2> backHolding;
		backHolding.push_back(Vector2(12, 2));
		backHolding.push_back(Vector2(13, 2));
		backHolding.push_back(Vector2(14, 2));

		shared_ptr<Action> backHAction = make_shared<Action>(backHolding, Action::Type::LOOP, 0.1f);

		_armActions.push_back(frontHAction);
		_armActions.push_back(sideHAction);
		_armActions.push_back(backHAction);
	}
#pragma endregion

}
