#pragma once
class BreakableItem : public DeployableObject
{
public:
	BreakableItem(string name, Vector2 pos, short hp = 1)
		:DeployableObject(DeployableObject::Type::BREAK, name, pos), _hp(hp)
	{}

	virtual ~BreakableItem() {}

	virtual void Interaction() override;

private:
	short _hp;
};

