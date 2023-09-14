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

	void SetPlayer(shared_ptr<PlayerImproved> p) { _player = p; }
	void SetMap(shared_ptr<TileMap> m) { _map = m; }

	void Use();
	void Charging();
	void StartCharging(int chargLevelInitial, float timeMax, int chargeMax, int levelPlus);
protected:
	void Hoe();
	void Water();
	void Fishing();
	void Break();
	void Weapon();
	void Eat();
	void Seed();
	void Fertilizer();
	void Collocate();

	string _subName;

	short _type = Type::BLANK;
	short _price;
	short _count = 0.0f;

	vector<short> _vals;

	float _timeMax;
	int _chargeMax;
	float _chargeTime;
	int _chargeLevel;
	int _levelPlus;


	Vector2 _point;

	weak_ptr<TileMap> _map;
	weak_ptr<PlayerImproved> _player;
};