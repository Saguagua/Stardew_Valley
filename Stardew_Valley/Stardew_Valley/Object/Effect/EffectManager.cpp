#include "framework.h"
#include "EffectManager.h"

EffectManager* EffectManager::_instance = nullptr;

EffectManager::EffectManager()
{
	vector<Vector2> indices;
	indices.push_back(Vector2(0,0));
	indices.push_back(Vector2(1,0));
	indices.push_back(Vector2(2,0));
	indices.push_back(Vector2(3,0));
	indices.push_back(Vector2(4,0));
	indices.push_back(Vector2(5,0));
	indices.push_back(Vector2(6,0));

	_breakAction = make_shared<Action>(indices, Action::Type::END, 0.1f);


	vector<Vector2> indices2;
	indices2.push_back(Vector2(0, 0));
	indices2.push_back(Vector2(1, 0));
	indices2.push_back(Vector2(2, 0));
	indices2.push_back(Vector2(3, 0));
	indices2.push_back(Vector2(4, 0));
	indices2.push_back(Vector2(5, 0));

	_deathAction = make_shared<Action>(indices2, Action::Type::END, 0.1f);


	for (int i = 0; i < 30; i++)
	{
		_damageEffects.push_back(make_shared<DamageEffect>());

		_effects.push_back(make_shared<Effect>(Vector2(40, 40), 0.5f));
	}


	vector<Vector2> indices3;
	indices3.push_back(Vector2(0, 0));

	_fishCatchAction = make_shared<Action>(indices3, Action::Type::END, 1.0f);

	_fishingEffect = make_shared<Effect>(Vector2(60, 50), 1.0f);
	_fishingEffect->SetAction(_fishCatchAction);
	_fishingEffect->SetImage("FishingEffectCatch");
}


void EffectManager::Render()
{

	for (int i = 0; i < 30; i++)
	{
		if (_damageEffects[i]->_isActive)
			_damageEffects[i]->Render();

		if (_effects[i]->_isActive)
			_effects[i]->Render();

	}
	if (_fishingEffect->_isActive)
		_fishingEffect->Render();
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

		if (_effects[i]->_isActive)
			_effects[i]->Update();

	}

	if (_fishingEffect->_isActive)
		_fishingEffect->Update();
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

void EffectManager::ActiveEffect(Vector2 pos, int type)
{
	for (int i = 0; i < _effects.size(); i++)
	{
		if (!_effects[i]->_isActive)
		{
			if (type == 0)
			{
				_effects[i]->SetAction(_breakAction);
				_effects[i]->SetImage("RockBreakEffect");
				_effects[i]->Active(pos, 0.6f);
			}
			else if (type == 1)
			{
				_effects[i]->SetAction(_deathAction);
				_effects[i]->SetImage("SlimeDeathEffect");
				_effects[i]->Active(pos, 0.6f);
			}
			else if (type == 2)
			{
				_fishingEffect->Active(pos, 1.0f);
			}

			break;
		}
	}
}
