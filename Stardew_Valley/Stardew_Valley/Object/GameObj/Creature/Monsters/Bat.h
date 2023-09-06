#pragma once
class Bat :public Monster
{
public:
	Bat();
	~Bat();

	void Render();
	void Update();

	void Move(Vector2 dir);
	float _power = 0.0f;
private:

	virtual void CreateAction() override;

};

