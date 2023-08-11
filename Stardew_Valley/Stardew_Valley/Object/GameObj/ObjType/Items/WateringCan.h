#pragma once
class WateringCan: public Item
{
public:
	WateringCan(string name)
		:Item(ObjectInfo::WATERINGCAN, 1) 
	{}
	
	virtual void KeyInput() override;
};

