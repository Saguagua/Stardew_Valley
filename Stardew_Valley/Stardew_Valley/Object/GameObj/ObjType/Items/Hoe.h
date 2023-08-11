#pragma once
class Hoe :public Item
{
public:
	Hoe(string name)
		:Item(ObjectInfo::Type::HOE,1)
	{}
	virtual void KeyInput() override;
};

