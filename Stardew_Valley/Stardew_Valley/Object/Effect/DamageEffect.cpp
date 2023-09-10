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

	Effect::Update();
}

void DamageEffect::Render()
{

	Effect::Render();

	_number->Render();
}

void DamageEffect::Active(Vector2 pos, float timer)
{
	Effect::Active(pos, timer);
	_number->_originPos = pos;
}
