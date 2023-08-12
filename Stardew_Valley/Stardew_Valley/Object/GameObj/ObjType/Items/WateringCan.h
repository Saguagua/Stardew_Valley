#pragma once
class WateringCan: public Item
{
public:
	WateringCan(string name)
		:Item(Item::WATERINGCAN, name, 1)
	{}
	
	virtual void KeyInput() override;
};

