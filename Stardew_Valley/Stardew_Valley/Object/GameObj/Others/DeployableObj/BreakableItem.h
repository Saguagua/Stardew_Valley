#pragma once
class BreakableItem : public DeployableObject
{
public:
	BreakableItem(string name, Vector2 pos, short breakType, short hp = 1)
		:DeployableObject(DeployableObject::Type::BREAK, name, pos), _breakType(breakType), _hp(hp)
	{}

	~BreakableItem() {}

	virtual void Interaction() override;
	virtual vector<int> GetProperty() override;
	void GetDamage(shared_ptr<Item> item);
private:
	short _hp;
	short _breakType;

};

