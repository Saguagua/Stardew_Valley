#pragma once
class Hoe :public Item
{
public:
	Hoe(string name)
		:Item(Item::Type::HOE, name, 1)
	{}
	virtual void KeyInput() override;
};

