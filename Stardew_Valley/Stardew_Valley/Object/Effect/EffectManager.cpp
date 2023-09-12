#include "framework.h"
#include "EffectManager.h"

EffectManager* EffectManager::_instance = nullptr;

EffectManager::EffectManager()
{
	for (int i = 0; i < 30; i++)
	{
		_damageEffects.push_back(make_shared<DamageEffect>());
	}
}


void EffectManager::Render()
{
	_count = 0;

	for (auto effect : _damageEffects)
	{
		if (!effect->_isActive)
			continue;

		effect->Render();
		_count++;
		if (_count > 1)
			_count = 0;
	}
}

void EffectManager::PostRender()
{
	ImGui::Text("EffectRenderCount : %d", _count);
	ImGui::Text("EffectActiveCount : %d", _activeCount);
}

void EffectManager::Update()
{
	for (auto effect : _damageEffects)
	{
		if (!effect->_isActive)
			continue;

		effect->Update();
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
			
			_activeCount++;
			break;
		}
	}
}
