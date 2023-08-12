#pragma once
#include "../../GameObject.h"

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
		FRTI,
		WEAPON,
		RING,
		SHOOSE,
		FACILITY
	};

	Item(Item::Type type, string name, short price, short count = 1)
		:GameObject(name), _type(type), _price(price), _count(count)
	{}

	virtual void KeyInput() {}


	bool AddCount();

	void SetCount(short count) { _count = count; }
	void SetPrice(short price) { _price = price; }
	void SetType(Item::Type type) { _type = type; }

	short GetCount() { return _count; }
	short GetPrice() { return _price; }
	Item::Type GetType() { return _type; }


protected:
	Item::Type _type;
	short _count;
	short _price;
};