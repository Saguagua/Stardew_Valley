#pragma once
class FishingRod:public Item
{
public:
	FishingRod(string name)
		:Item(ObjectInfo::Type::FISHINGROD, 1) 
	{}
	virtual void KeyInput() override;

private:
};

