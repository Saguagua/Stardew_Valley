#pragma once
class EatableItem : public GameObject
{
public:
	EatableItem(int itemCode, short count);
	~EatableItem() {}
	
	virtual void Interaction() override;
protected:
	short _maxHpCost;
	short _hpCost;
	short _maxStaminaCost;
	short _staminaCost;
	int _price;
};
