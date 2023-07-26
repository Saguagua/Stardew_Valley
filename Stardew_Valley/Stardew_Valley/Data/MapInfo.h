#pragma once
#include "framework.h"
#include "../Object/Tile/Tile.h"
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

	void SetName(string name) { _name = name; }
	void SetSize(Vector2 size) { _size = size; }
	void SetInfos(vector<shared_ptr<Tile>> infos) { _tiles = infos; }

private:
	string _name;
	Vector2 _size;
	vector<shared_ptr<Tile>> _tiles;
};

