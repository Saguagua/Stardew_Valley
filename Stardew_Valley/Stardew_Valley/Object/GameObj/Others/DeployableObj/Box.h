#pragma once
class Box :public DeployableObject
{
public:
	Box(string name, Vector2 pos);
	~Box() {}

	virtual void Interaction() override;
	virtual vector<int> GetProperty() override;

	virtual void Update() override;
private:
	shared_ptr<class Action> _action;

};

