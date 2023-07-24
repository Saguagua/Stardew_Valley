#include "framework.h"
#include "DataManager.h"
#include "PlayerInfo.h"
DataManager* DataManager::_instance = nullptr;

DataManager::DataManager()
{
	ReadTileTypes();
	ReadObjectFile();
	ReadMaps();
	ReadPlayerFile();
}

void DataManager::SaveMap(shared_ptr<MapInfo> info)
{
	string name = info->GetName();
	Vector2 size = info->GetSize();
	vector<shared_ptr<TileInfo>> infos = info->GetInfos();

	if (_mapTable.count(name) == false)
	{
		_mapTable[name] = true;

		_fout.open("Data/Contents/MapNames.txt", std::ios::app);
		_fout << endl << name;
		_fout.close();
	}

	_fout.open("Data/SaveFiles/" + name + ".txt");

	_fout << size.x << " " << size.y << endl;
	
	Vector2 tileFrame;
	Vector2 objectFrame;
	int tileIndex;
	int objectIndex;

	for (int i = 0; i < infos.size(); i++)
	{
		tileFrame = infos[i]->GetTileFrame();
		tileIndex = (int)tileFrame.x + (int)tileFrame.y * (int)_tileMaxFrame.x;
		_fout << tileIndex << " ";

		objectFrame = infos[i]->GetObjectFrame();
		objectIndex = (int)objectFrame.x + (int)objectFrame.y * (int)_objectMaxFrame.x;
		_fout << objectIndex;

		if ((i + 1) % (int)size.x == 0)
			_fout << endl;
		else
			_fout << " ";
	}

	_fout.close();
}

shared_ptr<MapInfo> DataManager::LoadMap(string mapName)
{
	ifstream fin;
	fin.open("Data/SaveFiles/" + mapName +".txt");

	if (!fin.is_open())
		return nullptr;

	Vector2 size;
	fin >> size.x;
	fin >> size.y;

	vector<shared_ptr<TileInfo>> infos;

	int tileIndex;
	int objectIndex;
	Vector2 tileFrame;
	Vector2 objectFrame;

	while (!fin.eof())
	{
		fin >> tileIndex;
		tileFrame.x = tileIndex % (int)_tileMaxFrame.x;
		tileFrame.y = tileIndex / (int)_tileMaxFrame.x;

		fin >> objectIndex;
		objectFrame.x = objectIndex % (int)_objectMaxFrame.x;
		objectFrame.y = objectIndex / (int)_objectMaxFrame.x;

		shared_ptr<TileInfo> info = make_shared<TileInfo>();
		info->SetTileFrame(tileFrame);
		info->SetObjectFrame(objectFrame);
		infos.push_back(info);
	}

	fin.close();

	if (infos.size() > 0)
		infos.pop_back();

	shared_ptr<MapInfo> mapInfo = make_shared<MapInfo>(mapName, size, infos);

	return mapInfo;
}

void DataManager::ReadMaps()
{
	_fin.open("Data/Contents/MapNames.txt");

	while (!_fin.eof())
	{
		string name;
		getline(_fin, name);
		_mapTable[name] = true;
		_mapInfos.push_back(LoadMap(name));
	}

	_fin.close();
}

void DataManager::ReadTileTypes()
{
	_fin.open("Data/Contents/TileTypes.txt");

	_fin >> _tileMaxFrame.x;
	_fin >> _tileMaxFrame.y;

	while (!_fin.eof())
	{
		int type;

		_fin >> type;
		_frameTypes.push_back(type);
	}

	_fin.close();
}

void DataManager::ReadObjectFile()
{
	_fin.open("Data/Contents/Object.txt");

	_fin >> _objectMaxFrame.x;
	_fin >> _objectMaxFrame.y;

	_fin.close();
}

void DataManager::ReadPlayerFile()
{
}
