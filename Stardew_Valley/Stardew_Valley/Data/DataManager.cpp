#include "framework.h"
#include "MapInfo.h"
#include "ObjectInfo.h"
#include "PlayerInfo.h"
#include "TileInfo.h"
#include "DataManager.h"

DataManager* DataManager::_instance = nullptr;

DataManager::DataManager()
{
	ReadTileTypes();
	ReadObjectFile();
	ReadPlayerFile();
}

void DataManager::SaveMaps(vector<shared_ptr<MapInfo>> infos)
{
	for (int i = 0; i < infos.size(); i++)
	{
		string name = infos[i]->GetName();
		Vector2 size = infos[i]->GetSize();
		vector<shared_ptr<Tile>> tileInfo = infos[i]->GetInfos();

		if (_mapTable.count(name) == false)
		{
			_mapTable[name] = true;

			_fout.open("Data/Contents/MapNames.txt", std::ios::app);
			_fout << endl << name;
			_fout.close();
		}

		_fout.open("Data/SaveFiles/" + name + ".txt");

		_fout << size.x << " " << size.y << endl;

		for (int i = 0; i < tileInfo.size(); i++)
		{
			_fout << tileInfo[i]->GetTileCode() << " ";
			_fout << tileInfo[i]->GetObjectCode();;

			if ((i + 1) % (int)size.x == 0)
				_fout << endl;
			else
				_fout << " ";
		}

		_fout.close();
	}
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

	vector<shared_ptr<Tile>> infos;

	int x = 0;
	int y = 0;
	int tileCode;
	int objectCode;

	while (!fin.eof())
	{
		fin >> tileCode;
		fin >> objectCode;

		Vector2 pos = Vector2(TILE_SIZE.x * x, TILE_SIZE.y * y) + TILE_SIZE * 0.5f;

		shared_ptr<Tile> info = make_shared<Tile>(pos, tileCode, objectCode);
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

		shared_ptr<TileInfo> info = make_shared<TileInfo>(type);
		_tileInfos.push_back(info);
	}

	_fin.close();
}

void DataManager::ReadObjectFile()
{
	_fin.open("Data/Contents/Object.txt");

	_fin >> _objectMaxFrame.x;
	_fin >> _objectMaxFrame.y;

	while (!_fin.eof())
	{
		string name;
		vector<int> vals;

		_fin >> name;
		for (int i = 0; i < 7; i++)
		{
			int tmp;
			_fin >> tmp;
			vals.push_back(tmp);
		}
		shared_ptr<ObjectInfo> obj = make_shared<ObjectInfo>(name, vals);
		_objInfos.push_back(obj);
	}
	_objInfos.pop_back();
	_fin.close();
}

void DataManager::ReadPlayerFile()
{
}
