#pragma once
class Item : public GameObject
{
public:
	Item(ObjectInfo::Type type, short price)
		:GameObject(type), _price(price)
	{}

	virtual void KeyInput() abstract;

	void SetPrice(short price) { _price = price; }
	short GetPrice() { return _price; }

protected:

	short _price;
};

