#pragma once
class Slime :public Creature
{
	enum SlimeAction
	{
		IDLE,
		MOVE,
		DEATH
	};
public:
	Slime();
	~Slime() {}

	void Update();

private:
	virtual void CreateAction() override;

	shared_ptr<CircleCollider> _detectArea;
};

