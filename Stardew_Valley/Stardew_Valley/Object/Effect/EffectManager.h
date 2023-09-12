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

private:
	static EffectManager* _instance;

	vector<shared_ptr<DamageEffect>> _damageEffects;
	int _count;
	int _activeCount = 0;
	
};

