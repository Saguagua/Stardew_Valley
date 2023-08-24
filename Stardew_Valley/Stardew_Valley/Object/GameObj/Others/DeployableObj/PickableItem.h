#pragma once
class PickableItem :public DeployableObject
{
public:
	PickableItem(string name, Vector2 pos) :DeployableObject(DeployableObject::Type::PICK, name, pos) {}

	~PickableItem() {}
	virtual void Interaction() override;
};

