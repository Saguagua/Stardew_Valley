#pragma once
class Axe :public Item
{
public:
	Axe(string name, short price)
		:Item(Item::Type::AXE, name, 0), _cost(0), _damage(0)
	{
	}

	virtual void KeyInput() override;

private:
	short _cost;
	short _damage;
};

