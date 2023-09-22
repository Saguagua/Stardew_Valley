#include "framework.h"
#include "FishingMinigame.h"

FishingMinigame::FishingMinigame()
{
	_bodySlot = make_shared<Transform>();
	_guageSlot = make_shared<Transform>();
	_fishSlot = make_shared<RectCollider>(Vector2(25, 30));
	_cursorSlot = make_shared<RectCollider>(Vector2(20, 60));

	_fishSlot->SetParent(_bodySlot);

	_guageSlot->SetParent(_bodySlot);

	_cursorSlot->SetParent(_bodySlot);

	_body = make_shared<Sprite>("FishingGame", Vector2(100, 300), SpriteType::UI);
	_fish = make_shared<Sprite>("FishingGameFish", Vector2(25, 30), SpriteType::UI);

	_guage = make_shared<SingleColorRect>(Vector2(10, 290));
	_cursor = make_shared<SingleColorRect>(Vector2(20, 60));

	_guageSlot->SetAngle(3.141592f);
}

FishingMinigame::~FishingMinigame()
{
}

void FishingMinigame::Update()
{
	if (!_isActive)
		return;

	if (_percent >= 100.0f)
		FishingSystem::GetInstance()->EndMinigame(true);
	else if (_percent <= 0.0f)
		FishingSystem::GetInstance()->EndMinigame(false);

	_bodySlot->Update();
	_fishSlot->Update();
	_guageSlot->Update();
	_cursorSlot->Update();

	Vector2 pos = _cursorSlot->GetWorldPos();

	if (pos.y <= _bodySlot->GetWorldPos().y - 110 && _power < 0)
	{
		_power = -_power * 0.7f;
	}
	else if (pos.y >= _bodySlot->GetWorldPos().y + 120 && _power > 0)
	{
		_power = -_power * 0.7f;
	}
	else
	{
		if (_power > _maxPower)
			_power -= GRAVITY * DELTA_TIME * 25.0f;
	}


	Vector2 fishPos = _fishSlot->GetWorldPos();

	if (fishPos.y <= _bodySlot->GetWorldPos().y - 110)
	{
		_fishPower = -_fishPower;
		_fishDirection = Vector2(0,1);
	}
	else if (fishPos.y >= _bodySlot->GetWorldPos().y + 120)
	{
		_fishPower = -_fishPower;
		_fishDirection = Vector2(0, -1);
	}
	else
	{
		if (_fishPower > _maxPower)
			_fishPower -= GRAVITY * DELTA_TIME * 25.0f;
	}


	_cursorSlot->AddPos(Vector2(0, 1) * DELTA_TIME * _power);

	if (_fishSlot->IsCollision(_cursorSlot))
	{
		_percent += 10 * DELTA_TIME;
		_fishCount += DELTA_TIME;
	}
	else
	{
		_percent -= 10 * DELTA_TIME;
	}


	if (_fishCount > 1.0f)
	{
		_fishCount = 0.0f;
		_fishPower = 200.0f;

		Vector2 dir = (fishPos - pos);
		dir.x = 0;
		_fishDirection = dir.Normalize();
	}

	if (_fishPower > 0.0f)
	{
		_fishSlot->AddPos(_fishDirection * DELTA_TIME * _fishPower);
	}

	

	Vector2 ratio = { 1.0f, _percent / 100.0f };
	_guage->SetRatio(ratio);

	KeyInput();
}

void FishingMinigame::Render()
{
	if (!_isActive)
		return;
	_bodySlot->Set_World();
	_body->Render();

	_guageSlot->Set_World();
	_guage->Render();

	_cursorSlot->GetTransform()->Set_World();
	_cursor->Render();

	_fishSlot->GetTransform()->Set_World();
	_fish->Render();
}

void FishingMinigame::SetActive(bool val)
{
	_isActive = val;
	_cursorSlot->SetPos(Vector2());
	_percent = 50.0f;
	_fishSlot->SetPos(Vector2(8, 0));
	_guageSlot->SetPos(Vector2(40, 0));
	_cursorSlot->SetPos(Vector2(6, 0));
	_fishPower = 0.0f;
	_fishCount = 0.0f;
}

void FishingMinigame::KeyInput()
{
	if (KEY_PRESS(VK_LBUTTON))
	{
		_power = 100.0f;
	}
}
