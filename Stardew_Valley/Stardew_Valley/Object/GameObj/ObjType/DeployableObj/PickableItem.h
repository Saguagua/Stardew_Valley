#pragma once
class PickableItem :public DeployableObject
{
public:
	PickableItem() :DeployableObject(ObjectInfo::Type::PICKABLE) {}

	virtual ~PickableItem() {}
	virtual void Interaction() override;

private:
	string _pickItemName;
};

