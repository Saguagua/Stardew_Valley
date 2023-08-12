#pragma once
class BreakableItem : public DeployableObject
{
public:
	BreakableItem(string name, Vector2 size)
		:DeployableObject(DeployableObject::Type::BREAK, name, size)
	{}

	virtual ~BreakableItem() {}

	virtual void Spawn(string name, shared_ptr<SpawnInfo> data) override;
	virtual void Interaction() override;

private:
	short _hp = 1;
};

