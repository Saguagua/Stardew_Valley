#include "framework.h"
#include "SaveManager.h"

SaveManager* SaveManager::_instance = nullptr;

SaveManager::SaveManager()
{
	ReadMaps();
	ReadTypes();
}

void SaveManager::SaveMap(shared_ptr<MapInfo> info)
{
	string name = info->GetName();
	Vector2 size = info->GetSize();
	vector<int> frames = info->GetFrames();

	if (_mapTable.count(name) == false)
	{
		_mapTable[name] = true;

		_fout.open("Map/Save/MapNames.txt", std::ios::app);
		_fout << name << endl;
		_fout.close();
	}

	_fout.open("Map/Save/" + name + ".txt");

	_fout << size.x << " " << size.y << endl;

	for (int i = 0; i < frames.size(); i++)
	{
		_fout << frames[i] << " ";
		if (i % (int)size.x == 0)
			_fout << endl;
	}

	_fout.close();
}

shared_ptr<MapInfo> SaveManager::LoadMap(string mapName)
{
	_fin.open("Map/Save/" + mapName +".txt");

	Vector2 size;

	_fin >> size.x;
	_fin >> size.y;

	vector<int> frames;

	while (!_fin.eof())
	{
		int frame;
		_fin >> frame;
		frames.push_back(frame);
	}

	_fin.close();

	shared_ptr<MapInfo> mapInfo = make_shared<MapInfo>(mapName, size, frames);

	return mapInfo;
}

void SaveManager::ReadMaps()
{
	_fin.open("Map/Save/MapNames.txt");

	while (!_fin.eof())
	{
		string name;
		getline(_fin, name);
		_mapTable[name] = true;
	}

	_fin.close();
}

void SaveManager::ReadTypes()
{
	_fin.open("Map/Save/ClipTypes.txt");

	while (!_fin.eof())
	{
		int type;

		_fin >> type;
		_clipTypes.push_back(type);
	}

	_fin.close();
}
