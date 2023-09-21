#include "framework.h"
#include "EffectManager.h"

EffectManager* EffectManager::_instance = nullptr;

EffectManager::EffectManager()
{
	for (int i = 0; i < 30; i++)
	{
		_damageEffects.push_back(make_shared<DamageEffect>());
		_breakEffects.push_back(make_shared<Effect>());
	}
}


void EffectManager::Render()
{

	for (int i = 0; i < 30; i++)
	{
		if (_damageEffects[i]->_isActive)
			_damageEffects[i]->Render();

		if (_breakEffects[i]->_isActive)
			_damageEffects[i]->Render();
	}
}

void EffectManager::PostRender()
{
}

void EffectManager::Update()
{
	for (int i = 0; i < 30; i++)
	{
		if (_damageEffects[i]->_isActive)
			_damageEffects[i]->Update();

		if (_breakEffects[i]->_isActive)
			_damageEffects[i]->Update();
	}
}

void EffectManager::ActiveDamage(int damge, Vector2 pos)
{
	for (int i = 0; i < _damageEffects.size(); i++)
	{
		if (!_damageEffects[i]->_isActive)
		{
			_damageEffects[i]->Active(pos, 0.5f);
			_damageEffects[i]->_number->SetNumber(damge);
	
			break;
		}
	}
}

void EffectManager::ActiveBreakEffect(Vector2 pos)
{
}
