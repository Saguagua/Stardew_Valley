#pragma once
#include "framework.h"
#include "../Object/Tile/Tile.h"

class PlayerInfo
{
public:

	PlayerInfo(string name, vector<short>& vals, Vector2 pos, vector<shared_ptr<class Item>> items)
		:_name(name), _maxHp(vals[0]), _hp(vals[1]), _maxStamina(vals[2]), _stamina(vals[3]), _pos(pos), _items(items)
	{}

	~PlayerInfo() {}

	string GetName() { return _name; }
	Vector2& GetPos() { return _pos; }

	short	       GetHP() { return _hp; }
	short	    GetMaxHP() { return _maxHp; }
	short	  GetStamina() { return _stamina; }
	short  GetMaxStamina() { return _maxStamina; }
	int		    GetState() { return _playerState; }
	int& GetStateRef() { return _playerState; }
	int GetCurIndex() { return _curIndex; }
	shared_ptr<Item> GetCurItem() { return _items[_curIndex]; }
	shared_ptr<Item> GetItem(int index) { return _items[index]; }
	vector<shared_ptr<Item>>& GetItems() { return _items; }

private:
	string _name;
	short _maxHp;
	short _hp;
	short _maxStamina;
	short _stamina;
	vector<shared_ptr<Item>> _items;
	Vector2 _pos;

	int _playerState = PlayerState::IDLE;
	int _curIndex = 0;
};

class LightInfo
{
public:
	LightInfo(XMFLOAT4 color, XMFLOAT4 pos) : _color(color), _pos(pos) {}
	~LightInfo() {}

	void SetColor(XMFLOAT4 color) { _color = color; }
	void SetPos(XMFLOAT4 pos) { _pos = pos; }

	XMFLOAT4 GetColor() { return _color; }
	XMFLOAT4 GetPos() { return _pos; }

private:
	XMFLOAT4 _color;
	XMFLOAT4 _pos;
};


class TeleportInfo
{
public:
	shared_ptr<RectCollider> _collider;
	int _destination;
	Vector2 _where;
};

class MapInfo
{
public:
	MapInfo(string name, Vector2 size, vector<shared_ptr<Tile>> tile)
		:_name(name), _size(size), _tiles(tile)
	{}

	~MapInfo() {}

	string GetName() { return _name; }
	Vector2 GetSize() { return _size; }
	vector<shared_ptr<Tile>>& GetInfos() { return _tiles; }
	vector<shared_ptr<TeleportInfo>>& GetTeleports() { return _teleports; }
	void SetName(string name) { _name = name; }
	void SetSize(Vector2 size) { _size = size; }
	void SetInfos(vector<shared_ptr<Tile>> infos) { _tiles = infos; }
	void SetTeleportInfo(vector<shared_ptr<TeleportInfo>> info) { _teleports = info; }
private:
	string _name;
	Vector2 _size;
	vector<shared_ptr<Tile>> _tiles;
	vector<shared_ptr<TeleportInfo>> _teleports;
};

struct XMLInfo
{
public:
	struct Position
	{
		int x;
		int y;
		int w;
		int h;
	};

	XMLInfo(string name)
		:_name(name) {}
	~XMLInfo() {}

	string GetName() { return _name; }
	const Position& GetPos(int index) { return _positions[index]; }
	const Vector2& GetSize(int index) { return _sizes[index]; }
	const wstring GetPage() { return _page; }

	void AddPosition(Position pos) { _positions.push_back(pos); }
	void AddSize(Vector2 size) { _sizes.push_back(size); }
	void SetPage(wstring page) { _page = page; }

private:
	string _name;
	vector<Position> _positions;
	vector<Vector2> _sizes;
	wstring _page;
};

struct DropInfo
{
public:
	struct Data
	{
		Data(string name, short percent)
			:_name(name), _percent(percent)
		{}

		string _name;
		short _percent;
	};

	DropInfo() {}
	~DropInfo() {}


	void AddDatas(string name, short percent) { _datas.push_back(Data(name, percent)); }

	vector<Data>& GetDatas() { return _datas; }

private:
	vector<Data> _datas;

};

struct DeployInfo
{
public:
	DeployInfo(short type, vector<short> vals)
		: _type(type), _vals(vals)
	{}

	short GetType() { return _type; }
	vector<short>& GetVals() { return _vals; }
	Vector2 GetSize() { return _size; }

	void SetSize(Vector2 size) { _size = size; }
private:
	short _type;
	vector<short> _vals;
	Vector2 _size = { 1,1 };
};

struct ItemInfo
{
public:
	ItemInfo(string subName, short type, short price, vector<short> vals)
		: _subName(subName), _type(type), _price(price), _vals(vals)
	{}

	string GetSubName() { return _subName; }
	short GetType() { return _type; }
	short GetPrice() { return _price; }
	vector<short>& GetVals() { return _vals; }

private:
	string _subName;
	short _type;
	short _price;
	vector<short> _vals;
};

struct CropInfo
{
public:

private:
	short _period;
	short _spawnCount;
};


struct FishInfo
{
public:


	void AddFishInfo(string name, short percent)
	{
		_fishNames.push_back(name);
		_percents.push_back(percent);
		_size++;
	}


	vector<string> _fishNames;
	vector<short> _percents;
	UINT _size = 0;
};