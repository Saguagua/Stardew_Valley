#pragma once
class PickAxe: public GameObject
{
public:
	PickAxe(int objCode, int frameIndex,  short cost, short damage)
		:GameObject(objCode, frameIndex, 1, 1), _cost(cost), _damage(damage)
	{
		_type = ObjectInfo::Type::PICKAXE;
	}
	virtual ~PickAxe() {}

	short GetDamage() { return _damage; }
	short GetCost() { return _cost; }

private:
	short _damage;
	short _cost;
};

