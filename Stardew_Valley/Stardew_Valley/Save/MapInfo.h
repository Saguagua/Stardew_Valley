#pragma once
#include "framework.h"

class MapInfo
{
public:
	MapInfo(string name, Vector2 size, vector<shared_ptr<TileInfo>> infos)
		:_name(name), _size(size), _infos(infos)
	{}

	~MapInfo() {}

	string GetName() { return _name; }
	Vector2 GetSize() { return _size; }
	vector<shared_ptr<TileInfo>>& GetInfos() { return _infos; }

	void SetName(string name) { _name = name; }
	void SetSize(Vector2 size) { _size = size; }
	void SetInfos(vector<shared_ptr<TileInfo>> infos) { _infos = infos; }

private:
	string _name;
	Vector2 _size;
	vector<shared_ptr<TileInfo>> _infos;
};

