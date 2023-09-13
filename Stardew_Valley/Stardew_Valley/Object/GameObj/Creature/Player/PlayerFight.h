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

	bool _isAttacking = false;
	shared_ptr<RectCollider> _weaponCollider;
	shared_ptr<Transform> _weaponSlot;
	float _attackCount = 0.0f;
	shared_ptr<Sprite> _weapon;



private:
	void SetFreeze(bool val) { _freeze = val; }
	void SetIdle();
	virtual void CreateAction() override;

	shared_ptr<Transform> _weaponRotate;
};