#pragma once
class DamageEffect :public Effect
{
public:
	DamageEffect();
	~DamageEffect() {}

	void Update();
	void Render();

	void Active(Vector2 pos, float timer);

	shared_ptr<class NumberUI> _number;
};

