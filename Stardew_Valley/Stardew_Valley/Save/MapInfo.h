#pragma once
#include "framework.h"

class MapInfo
{
public:
	MapInfo(string name, Vector2 size, vector<int> frames)
		:_name(name), _size(size), _frames(frames)
	{}

	~MapInfo() {}

	string GetName() { return _name; }
	Vector2 GetSize() { return _size; }
	vector<int>& GetFrames() { return _frames; }

	string SetName(string name) { _name = name; }
	Vector2 SetSize(Vector2 size) { _size = size; }
	vector<int>& SetFrames(vector<int> frames) { _frames = frames; }

private:
	string _name;
	Vector2 _size;
	vector<int> _frames;
};

