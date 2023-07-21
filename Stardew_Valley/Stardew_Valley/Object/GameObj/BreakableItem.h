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
};

