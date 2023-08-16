#pragma once
class PickableItem :public DeployableObject
{
public:
	PickableItem(string name) :DeployableObject(DeployableObject::Type::PICK, name) {}

	virtual ~PickableItem() {}
	virtual void Interaction() override;
};

