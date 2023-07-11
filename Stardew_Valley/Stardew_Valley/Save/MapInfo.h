#pragma once
#include "framework.h"

class MapInfo
{
public:
	MapInfo(string name, Vector2 size, vector<int> clips)
		:_name(name), _size(size), _clips(clips)
	{}

	~MapInfo() {}

	string GetName() { return _name; }
	Vector2 GetSize() { return _size; }
	vector<int>& GetClips() { return _clips; }

	string SetName(string name) { _name = name; }
	Vector2 SetSize(Vector2 size) { _size = size; }
	vector<int>& SetClips(vector<int> clips) { _clips = clips; }

private:
	string _name;
	Vector2 _size;
	vector<int> _clips;
};

