#pragma once
#define LEVEL 0
#define COST 1

class PlayerImproved;
class TileMap;

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
		FACILITY,
		BLANK
	};

	Item()
		:GameObject("BLANK")
	{}

	virtual ~Item() {}

	void SetItem(string name, short count);

	bool AddCount();

	short GetCount() { return _count; }
	short GetPrice() { return _price; }
	short GetType() { return _type; }

	const vector<short>& GetVals() { return _vals; }

	void Hoe(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m);
	void Water(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m);
	void Break(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m);
	void Fishing(shared_ptr<PlayerImproved> p);
	void Weapon(shared_ptr<PlayerImproved> p);
	void Eat(shared_ptr<PlayerImproved> p);
	void Seed(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m);
	void Fertilizer(shared_ptr<PlayerImproved> p, shared_ptr<TileMap> m);

protected:
	string _subName;

	short _type = Type::BLANK;
	short _price;
	short _count;

	vector<short> _vals;

	float _chargeTime;
	float _chargeCount;

	Vector2 _point;
};