#pragma once
#include "../../GameObject.h"
#define LEVEL 0
#define COST 1

class Item : public GameObject
{
public:
	enum Type
	{
		NONE,
		AXE,
		EATABLE,
		FISHINGROD,
		HOE,
		PICKAXE,
		WATERINGCAN,
		SEED,
		FERTILIZER,
		WEAPON,
		RING,
		SHOOSE,
		FACILITY
	};

	Item()
		:GameObject("BLANK")
	{}

	void KeyInput();

	void SetItem(string name, short count);

	bool AddCount();

	short GetCount() { return _count; }
	short GetPrice() { return _price; }
	short GetType() { return _type; }

protected:
	void Hoe();
	void Water();
	void Axe();
	void PickAxe();
	void Fishing();
	void Weapon();
	void Eat();
	void Seed();
	void Fertilizer();

	string _subName;

	short _type;
	short _price;
	short _count;
	vector<short> _vals;
	float _chargeTime;
	float _chargeCount;
	Vector2 _point;
};