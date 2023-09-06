#pragma once
#define FRONT 0
#define SIDE 1
#define BACK 2

class PlayerFight :public PlayerImproved
{
public:
	PlayerFight();
	~PlayerFight() {}

	void Render();
	void Update();

	void AddMaxHP(short cost);
	void AddMaxStamina(short cost);
	virtual void AddHP(short cost) override;
	void AddStamina(short cost);
	bool _isAttacking = false;
	shared_ptr<RectCollider> _weaponCollider;
private:
	shared_ptr<Transform> _weaponSlot;

	float _attackCount = 0.0f;
};

