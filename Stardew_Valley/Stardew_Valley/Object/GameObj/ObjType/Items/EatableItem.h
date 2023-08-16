#pragma once
class EatableItem : public Item
{
public:
	EatableItem(string name, short price, vector<short> vals)
		: Item(Item::Type::EATABLE, name, price),
		_maxHpCost(vals[0]), _maxStaminaCost(vals[1]), _hpCost(vals[2]), _staminaCost(vals[3])
	{}
	~EatableItem() {}
	
	virtual void KeyInput() override;
protected:
	short _maxHpCost;
	short _hpCost;
	short _maxStaminaCost;
	short _staminaCost;
};
