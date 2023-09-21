#pragma once
class BreakableItem : public DeployableObject
{
public:
	BreakableItem(string name, Vector2 pos, short hp = 1)
		:DeployableObject(DeployableObject::Type::BREAK, name, pos), _hp(hp)
	{
		_breakType = DATA->GetDeployInfo(_name)->GetVals()[0];
	}

	~BreakableItem() {}

	virtual vector<int> GetProperty() override;
	virtual void GetDamage(shared_ptr<Item> item);
protected:
	short _hp;
	short _breakType;
};

