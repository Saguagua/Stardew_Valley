#pragma once
class PlayerImproved: public Player
{
public:
	PlayerImproved();
	~PlayerImproved() {}

	void PlayAction();

private:
	list<PlayerSubscribe*> _subscribers;

	float _chargeTime;
	float _chargeCount;
	Vector2 _chargePoint;
};

