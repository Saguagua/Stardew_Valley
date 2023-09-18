#pragma once
class Bed :public DeployableObject
{
public:
	Bed(string name, Vector2 pos);

	~Bed() {}

	virtual void Interaction() override;
	virtual vector<int> GetProperty() override;

private:
	void SceneChange();

	CallBack _cb;
};

