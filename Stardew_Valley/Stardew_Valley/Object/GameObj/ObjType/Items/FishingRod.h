#pragma once
class FishingRod:public Item
{
public:
	FishingRod(string name)
		:Item(Item::Type::FISHINGROD, name, 1)
	{}
	virtual void KeyInput() override;

private:
};

