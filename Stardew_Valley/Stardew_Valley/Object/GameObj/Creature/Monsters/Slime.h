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

	virtual void Detect(shared_ptr<PlayerImproved> col) override;

	float _chargeCount = 0;
	float _jumpPower = 0;


private:
	virtual void CreateAction() override;

	void Charging();

	shared_ptr<LightTextureRect> _eye;

	shared_ptr<Transform> _eyeSlot;

	UINT _eyeIndex = SlimeAction::EYEIDLE;
	float _stopTimer = 3.0f;


	virtual void Initialize() override;

};

