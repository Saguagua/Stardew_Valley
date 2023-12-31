#pragma once
class Bat :public Monster
{
public:
	Bat();
	~Bat();

	void Render();
	void Update();

	virtual void Detect(shared_ptr<PlayerImproved> player) override;

private:
	virtual void CreateAction() override;
	virtual void Initialize() override;

};

