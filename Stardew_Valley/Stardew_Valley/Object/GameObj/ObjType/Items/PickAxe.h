#pragma once
class PickAxe: public Item
{
public:
	PickAxe(string name)
		:Item(Item::Type::PICKAXE, name, 1), _cost(0), _damage(0)
	{
	}
	virtual ~PickAxe() {}

	short GetDamage() { return _damage; }
	short GetCost() { return _cost; }

	virtual void KeyInput() override;

private:
	short _damage;
	short _cost;
};

