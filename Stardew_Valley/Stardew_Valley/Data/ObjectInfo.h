#pragma once
#include "framework.h"

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

	void AddPosition(Position pos) { _positions.push_back(pos); }

private:
	string _name;
	vector<Position> _positions;
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

private:
	short _type;
	vector<short> _vals;
};

struct ItemInfo
{
public:
	ItemInfo(short type, short price, vector<short> vals)
		: _type(type), _price(price), _vals(vals)
	{}

	short GetType() { return _type; }
	short GetPrice() { return _price; }
	vector<short>& GetVals() { return _vals; }

private:
	short _type;
	short _price;
	vector<short> _vals;
};