#pragma once
class Slime :public Monster
{
	enum SlimeAction
	{
		IDLE,
		MOVE,
		DEATH,
		EYEIDLE,
		EYESURPRISE,
		EYEANGRY,
	};
public:
	Slime();
	~Slime() {}

	void Update();
	void Render();

private:
	virtual void CreateAction() override;

	shared_ptr<LightTextureRect> _eye;

	shared_ptr<Transform> _eyeSlot;

	UINT _eyeIndex = SlimeAction::EYEIDLE;
};

