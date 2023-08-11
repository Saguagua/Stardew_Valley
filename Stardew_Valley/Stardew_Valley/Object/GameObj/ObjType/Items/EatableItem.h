#pragma once
class EatableItem : public Item
{
public:
	EatableItem(string name, vector<short> vals)
		: Item(ObjectInfo::Type::EATABLE, vals[6]),
		_maxHpCost(vals[2]), _maxStaminaCost(vals[3]), _hpCost(vals[4]), _staminaCost(vals[5])
	{}
	~EatableItem() {}
	
	virtual void KeyInput() override;
protected:
	short _maxHpCost;
	short _hpCost;
	short _maxStaminaCost;
	short _staminaCost;
};
