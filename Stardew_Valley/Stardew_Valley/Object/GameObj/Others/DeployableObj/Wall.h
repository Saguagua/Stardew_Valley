#pragma once
class Wall :public DeployableObject
{
public:
	Wall(string name, Vector2 pos) :DeployableObject(DeployableObject::Type::WALL, name, pos) {}
	~Wall() {}


	virtual vector<int> GetProperty() override;
};