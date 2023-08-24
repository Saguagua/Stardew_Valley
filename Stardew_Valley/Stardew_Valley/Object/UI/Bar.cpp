#include "framework.h"
#include "Bar.h"

Bar::Bar(shared_ptr<PlayerImproved> player, wstring path, string name, Vector2 size)
	:PlayerSubscribe(player, PlayerSubscribe::Type::ALL)
{
	if (name == "HPBar")
		SetType(Type::HP);
	else
		SetType(Type::STAMINA);

	_player = player;
	_player.lock()->RequestSubscribe(this);

	_bodyTransform = make_shared<Transform>();
	_guageTransform = make_shared<Transform>();
	_body = make_shared<Sprite>(path, name, size, SpriteType::UI);
	_gauge = make_shared<SingleColorRect>(size - Vector2(20, 55));

	_guageTransform->SetPos(Vector2(0, -20));
	_guageTransform->SetAngle(PI);
	_guageTransform->SetParent(_bodyTransform);
}

void Bar::Render()
{
	_bodyTransform->Set_World();
	_body->Render();
	_guageTransform->Set_World();
	_gauge->Render();
}

void Bar::SetRatio(Vector2 ratio)
{
	Vector2 curRatio = _gauge->GetRatio();
	XMFLOAT4 color = _gauge->GetColor();
	float del = curRatio.y - ratio.y;

	if (del > 0)
	{
		if (color.x == 1)
			_gauge->AddColor(XMFLOAT4(0.0f, -del * 2, 0.0f, 0.0f));
		else
			_gauge->AddColor(XMFLOAT4(del * 2, 0.0f, 0.0f, 0.0f));
	}
	else if (del < 0)
	{
		if (color.y == 1)
			_gauge->AddColor(XMFLOAT4(-del * 2, 0.0f, 0.0f, 0.0f));
		else
			_gauge->AddColor(XMFLOAT4(0.0f, del * 2, 0.0f, 0.0f));
	}

	_gauge->SetRatio(ratio);
}

void Bar::SetPos(Vector2 pos)
{
	_bodyTransform->SetPos(pos);
	_bodyTransform->Update();
	_guageTransform->Update();
}

void Bar::UpdateInfo()
{
	if (_type == Type::HP)
		SetRatio(Vector2(1.0f, (float)_player.lock()->GetHp()));
	else
		SetRatio(Vector2(1.0f, (float)_player.lock()->GetStamina()));
}

void Bar::Dead()
{
}
