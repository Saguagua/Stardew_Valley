#pragma once
class EatableItem : public GameObject
{
public:
	EatableItem(int itemCode, int frameIndex, short maxHp, short hp, short maxStamina, short stamina,  short maxCount, short count = 1)
	: GameObject(itemCode, frameIndex, maxCount, count),
		_maxHpCost(maxHp), _hpCost(hp), _maxStaminaCost(maxStamina), _staminaCost(stamina)
	{
		_type = ObjectInfo::Type::EATABLE;
	}
	~EatableItem() {}
	
	virtual void Interaction() override;
protected:
	short _maxHpCost;
	short _hpCost;
	short _maxStaminaCost;
	short _staminaCost;
	int _price;
};
