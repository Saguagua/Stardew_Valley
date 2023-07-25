#pragma once
class BreakableItem : public GameObject
{
public:
	BreakableItem(int itemCode);
	~BreakableItem() {}

	void CreateAction();

protected:
	void GetDamage(int amount);

	int _hp;

	// GameObject을(를) 통해 상속됨
	virtual int UseItem() override;
};

