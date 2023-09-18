#pragma once
class Door :public DeployableObject
{
public:
	Door(string name, Vector2 pos);
	~Door() {}

	// DeployableObject을(를) 통해 상속됨
	virtual void Interaction() override;
	virtual vector<int> GetProperty() override;

private:
	CallBack _cb;
};

