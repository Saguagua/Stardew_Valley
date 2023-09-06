#pragma once
#define LEVEL 0
#define COST 1

class PlayerFight;
class TileMap;

class Item : public GameObject, public enable_shared_from_this<Item>
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

	void Hoe(shared_ptr<PlayerFight> p, shared_ptr<TileMap> m);
	void Water(shared_ptr<PlayerFight> p, shared_ptr<TileMap> m);
	void Break(shared_ptr<PlayerFight> p, shared_ptr<TileMap> m);
	void Fishing(shared_ptr<PlayerFight> p);
	void Weapon(shared_ptr<PlayerFight> p);
	void Eat(shared_ptr<PlayerFight> p);
	void Seed(shared_ptr<PlayerFight> p, shared_ptr<TileMap> m);
	void Fertilizer(shared_ptr<PlayerFight> p, shared_ptr<TileMap> m);

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