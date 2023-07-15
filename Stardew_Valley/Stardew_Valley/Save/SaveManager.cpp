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

		_fout.open("Save/Contents/MapNames.txt", std::ios::app);
		_fout << endl << name;
		_fout.close();
	}

	_fout.open("Save/SaveFiles/" + name + ".txt");

	_fout << size.x << " " << size.y << endl;
	int Size = size.x * size.y;
	for (int i = 0; i < Size; i++)
	{
		int frame = frames[i].x + frames[i].y * 13;
		_fout << frame;
		if ((i + 1) % (int)size.x == 0)
			_fout << endl;
		else
			_fout << " ";
	}

	_fout.close();
}

shared_ptr<MapInfo> SaveManager::LoadMap(string mapName)
{
	ifstream fin;
	fin.open("Save/SaveFiles/" + mapName +".txt");

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

	if (frames.size() > 0)
		frames.pop_back();

	shared_ptr<MapInfo> mapInfo = make_shared<MapInfo>(mapName, size, frames);

	return mapInfo;
}

void SaveManager::ReadMaps()
{
	_fin.open("Save/Contents/MapNames.txt");

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
	_fin.open("Save/Contents/TileTypes.txt");

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
