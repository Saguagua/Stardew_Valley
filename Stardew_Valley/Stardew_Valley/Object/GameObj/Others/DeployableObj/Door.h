#pragma once
class Door :public DeployableObject
{
public:
	Door(string name, Vector2 pos);
	~Door() {}

	// DeployableObject��(��) ���� ��ӵ�
	virtual void Interaction() override;
	virtual vector<int> GetProperty() override;

private:
	CallBack _cb;
};

