#pragma once
#include "../../Data/PlayerSubscribe.h"

class Player: public PlayerSubscribe
{
	enum PlayerAction
	{
		FRONTIDLE,
		SIDEIDLE,
		BACKIDLE,
		FRONTRUN,
		SIDERUN,
		BACKRUN,
		FRONTHOLD,
		SIDEHOLD,
		BACKHOLD
	};


public:
	Player();
	~Player() {}

	void Update();
	void Render();

	void SetSelectedItemIndex(int index);
	virtual void UpdateInfo() override;
	virtual void Dead() override;

private:
	void CreateAction();
	void SetAction(int index);
	void SetRun(int index);

	void KeyInput();
	void Move();
	void Items();

	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _itemSlot;
	shared_ptr<class LightTextureRect> _body;
	shared_ptr<LightTextureRect> _arm;
	shared_ptr<LightTextureRect> _obj;

	vector<shared_ptr<Action>> _bodyActions;
	vector<shared_ptr<Action>> _armActions;

	int _bodyIndex = PlayerAction::FRONTIDLE;
	int _armIndex = PlayerAction::FRONTIDLE;

};