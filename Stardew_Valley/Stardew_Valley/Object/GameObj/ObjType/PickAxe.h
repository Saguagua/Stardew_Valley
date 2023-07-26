#pragma once
class PickAxe: public GameObject
{
public:
	PickAxe(int itemCode, int damage, int cost)
		:GameObject(itemCode), _damage(damage), _cost(cost) {}
	virtual ~PickAxe() {}

	virtual void UseItem() override;
private:
	short _damage;
	short _cost;
};

