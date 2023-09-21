#include "framework.h"
#include "Effect.h"

Effect::Effect(Vector2 size, float timer)
	:_size(size), _timer(timer)
{
	_transform = make_shared<Transform>();
	_renderer = make_shared<Sprite>("BLANK", _size, SpriteType::UI);
}

void Effect::Update()
{
	_action->Update();
	_renderer->SetIndex(_action->GetCurFrame().x);

	_transform->Update();
	_timer -= DELTA_TIME;

	if (_timer <= 0.0f)
		_isActive = false;
}

void Effect::Render()
{
	_transform->Set_World();
	_renderer->Render();
}

void Effect::SetImage(string name, int index)
{
	_renderer->SetImage(name, index);
}

void Effect::Active(Vector2 pos, float timer)
{
	_transform->SetPos(pos);
	_transform->Update();

	_timer = timer;

	_isActive = true;
	_action->Play();
}
