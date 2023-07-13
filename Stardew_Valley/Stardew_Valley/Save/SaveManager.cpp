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
	vector<Vector2> frames = info->GetFrames();

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
		int frame = frames[i].x + frames[i].y * 13;
		_fout << frame << " ";
		if (i % (int)size.x == 0)
			_fout << endl;
	}

	_fout.close();
}

shared_ptr<MapInfo> SaveManager::LoadMap(string mapName)
{
	ifstream fin;
	fin.open("Map/Save/" + mapName +".txt");

	if (!fin.is_open())
		return nullptr;
	Vector2 size;
	fin >> size.x;
	fin >> size.y;

	vector<Vector2> frames;

	while (!fin.eof())
	{
		int tmp;
		fin >> tmp;
		Vector2 frame;
		frame.x = tmp % 13;
		frame.y = tmp / 13;
		frames.push_back(frame);
	}

	fin.close();

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
		_mapInfos.push_back(LoadMap(name));
	}

	_fin.close();
}

void SaveManager::ReadTypes()
{
	_fin.open("Map/Save/ClipTypes.txt");

	_fin >> _maxFrame.x;
	_fin >> _maxFrame.y;

	while (!_fin.eof())
	{
		int type;

		_fin >> type;
		_frameTypes.push_back(type);
	}

	_fin.close();
}
