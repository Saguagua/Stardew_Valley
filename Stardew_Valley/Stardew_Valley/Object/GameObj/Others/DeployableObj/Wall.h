#pragma once
class Wall :public DeployableObject
{
public:
	Wall(string name, Vector2 pos) :DeployableObject(DeployableObject::Type::WALL, name, pos) {}
	~Wall() {}


	virtual void Interaction() override;
	virtual vector<int> GetProperty() override;
};

