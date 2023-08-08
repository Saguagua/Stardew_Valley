#pragma once
class EatableItem : public GameObject
{
public:
	EatableItem(int itemCode, vector<short> vals)
	: GameObject(itemCode, vals[1], vals[7], 1),
		_maxHpCost(vals[2]), _maxStaminaCost(vals[3]), _hpCost(vals[4]), _staminaCost(vals[5]), _price(vals[6])
	{
		_type = ObjectInfo::Type::EATABLE;
	}
	~EatableItem() {}
	
	virtual void KeyInput() override;
protected:
	short _maxHpCost;
	short _hpCost;
	short _maxStaminaCost;
	short _staminaCost;
	int _price;
};
