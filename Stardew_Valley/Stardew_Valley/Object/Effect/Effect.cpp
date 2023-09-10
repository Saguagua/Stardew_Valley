#include "framework.h"
#include "Effect.h"

Effect::Effect(Vector2 size, float timer)
	:_size(size), _timer(timer)
{
	_transform = make_shared<Transform>();
}

void Effect::Update()
{
	_transform->Update();
	_timer -= DELTA_TIME;

	if (_timer <= 0.0f)
		_isActive = false;
}

void Effect::Render()
{
	_transform->Set_World();
}

void Effect::Active(Vector2 pos, float timer)
{
	_transform->SetPos(pos);
	_transform->Update();

	_timer = timer;

	_isActive = true;
}
