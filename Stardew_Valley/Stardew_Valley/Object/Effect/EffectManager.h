#pragma once
class EffectManager
{
	EffectManager();
	~EffectManager() {}

public:
	static void Create()
    {
		if (_instance == nullptr)
			_instance = new EffectManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static EffectManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Render();
	void PostRender();
	void Update();

	void ActiveDamage(int damge, Vector2 pos);
	void ActiveEffect(Vector2 pos, int type);
private:
	static EffectManager* _instance;

	shared_ptr<Action> _breakAction;
	shared_ptr<Action> _deathAction;
	shared_ptr<Action> _fishCatchAction;

	vector<shared_ptr<DamageEffect>> _damageEffects;
	vector<shared_ptr<Effect>> _effects;
	shared_ptr<Effect> _fishingEffect;
};

