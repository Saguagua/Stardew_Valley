#pragma once
#include "../../Data/PlayerSubscribe.h"

class Player: public PlayerSubscribe
{
	enum PlayerAction
	{
		IDLE = 0,
		RUN = 3,
		TOOL = 6,
		HOLD = 9,
	};

	enum Direction
	{
		FRONT = 0,
		SIDE = 1,
		BACK = 2
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
	void Mouse();

	shared_ptr<Transform> _bodySlot;
	shared_ptr<Transform> _itemSlot;
	shared_ptr<class LightTextureRect> _body;
	shared_ptr<LightTextureRect> _arm;
	shared_ptr<LightTextureRect> _obj;

	vector<shared_ptr<Action>> _bodyActions;
	vector<shared_ptr<Action>> _armActions;

	int _bodyIndex = PlayerAction::IDLE;
	int _armIndex = PlayerAction::IDLE;
	Direction _dir = Direction::FRONT;
};