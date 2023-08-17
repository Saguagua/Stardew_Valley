#pragma once
class Hoe :public Item
{
public:
	Hoe(string name, short price, short level)
		:Item(Item::Type::HOE, name, price), _level(level)
	{}
	virtual void KeyInput() override;
private:
	short _cost = -5;
	short _level;
	float _chargeTime = 0;
	int _chargeCount = 0;

	vector<shared_ptr<Tile>> _tiles;
	Vector2 _point;
};

