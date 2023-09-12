#include "framework.h"
#include "../UI/NumberUI.h"
#include "DamageEffect.h"

DamageEffect::DamageEffect()
	:Effect(Vector2(20, 20), 1.0f)
{
	_number = make_shared<NumberUI>(0, 1, _size);
}

void DamageEffect::Update()
{
	_timer -= DELTA_TIME;

	if (_timer <= 0.0f)
		_isActive = false;
}

void DamageEffect::Render()
{
	_number->Render();
}

void DamageEffect::Active(Vector2 pos, float timer)
{
	_number->_originPos = pos;
	_timer = timer;
	_isActive = true;
}
