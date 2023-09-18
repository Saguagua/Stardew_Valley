#pragma once
class Elevator :public DeployableObject
{
public:
	Elevator(string name, Vector2 pos);
	~Elevator() {}

	virtual void Interaction() override;

	virtual vector<int> GetProperty() override;

private:

	CallBack _cb;
};

