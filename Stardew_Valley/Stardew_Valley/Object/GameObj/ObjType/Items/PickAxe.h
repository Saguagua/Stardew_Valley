#pragma once
class PickAxe: public Item
{
public:
	PickAxe(string name)
		:Item(ObjectInfo::Type::PICKAXE, 1), _cost(0), _damage(0)
	{
		_type = ObjectInfo::Type::PICKAXE;
	}
	virtual ~PickAxe() {}

	short GetDamage() { return _damage; }
	short GetCost() { return _cost; }

	virtual void KeyInput() override;

private:
	short _damage;
	short _cost;
};

