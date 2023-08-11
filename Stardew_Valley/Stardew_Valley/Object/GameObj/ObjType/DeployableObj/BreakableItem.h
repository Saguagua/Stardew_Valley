#pragma once
class BreakableItem : public DeployableObject
{
public:
	BreakableItem() 
		:DeployableObject(ObjectInfo::Type::BREAKABLE) 
	{}

	virtual ~BreakableItem() {}

	virtual void Spawn(string name, SpawnInfo data) override;
	virtual void Interaction() override;

private:
	short _hp;
	vector<string> _dropTable; //수정 필요
	short _countMax;
};

