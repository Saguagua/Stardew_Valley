#pragma once
class BreakableItem : public DeployableObject
{
public:
	BreakableItem(string name, Vector2 size, short hp = 1)
		:DeployableObject(DeployableObject::Type::BREAK, name, size), _hp(hp)
	{}

	virtual ~BreakableItem() {}

	virtual void Spawn(string name, shared_ptr<SpawnInfo> data) override;
	virtual void Interaction() override;

private:
	short _hp;
};

