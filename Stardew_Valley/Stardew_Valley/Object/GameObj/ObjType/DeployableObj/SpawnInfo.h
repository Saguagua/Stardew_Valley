#pragma once
struct SpawnInfo
{
	SpawnInfo(void* data):_data(data)
	{}

	~SpawnInfo() { delete _data; }

	void* _data;
};