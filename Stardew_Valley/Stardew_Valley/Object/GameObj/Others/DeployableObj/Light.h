#pragma once
class Light :public DeployableObject
{
public:
	Light(string name, Vector2 pos, int lightIndex);
	~Light() {}

private:
	virtual void Interaction() override;
	virtual vector<int> GetProperty() override;

	short _hp = 1;
	int _lightIndex;
};

