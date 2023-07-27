#include <atlstr.h>
#include "framework.h"
#include "MapInfo.h"
#include "ObjectInfo.h"
#include "PlayerInfo.h"
#include "TileInfo.h"
#include "../Object/Tile/TileType/ArableTile.h"
#include "../Object/Tile/TileType/FishableTile.h"
#include "DataManager.h"

DataManager* DataManager::_instance = nullptr;


DataManager::DataManager()
{
	ReadMaps();
	ReadTileTypes();
	ReadObjectFile();
	ReadPlayers();
}

void DataManager::Save()
{
	CString path;
	TCHAR programPath[_MAX_PATH];
	GetModuleFileName(NULL, programPath, _MAX_PATH);
	GetCurrentDirectory(_MAX_PATH, programPath);
	path += programPath;
	path += L"/";
	path += PLAYER->GetPlayerInfo()->GetName().c_str();
	CreateDirectory(path, NULL);

	SaveMaps();
	SavePlayerInfo();
}

void DataManager::Load(string name)
{
	for (pair<string, bool> iter : _mapTable)
	{
		LoadMap(name, iter.first);
	}

	LoadPlayerInfo(name);
}

void DataManager::SaveMaps()
{
	vector<shared_ptr<MapInfo>> infos = TILEMAP->GetMapInfos();
	string playerName = PLAYER->GetPlayerInfo()->GetName();
	ofstream fout;

	for (int i = 0; i < infos.size(); i++)
	{
		string mapName = infos[i]->GetName();
		Vector2 size = infos[i]->GetSize();
		vector<shared_ptr<Tile>> tileInfo = infos[i]->GetInfos();

		if (_mapTable.count(mapName) == false)
		{
			_mapTable[mapName] = true;

			fout.open("Data/Contents/MapNames.txt", std::ios::app);
			fout << endl << mapName;
			fout.close();
		}

		fout.open("Data/SaveFiles/" + playerName + "/" + mapName + ".txt");

		fout << size.x << " " << size.y << endl;

		for (int i = 0; i < tileInfo.size(); i++)
		{
			fout << tileInfo[i]->GetTileCode() << " ";
			fout << tileInfo[i]->GetObjectCode();;

			if ((i + 1) % (int)size.x == 0)
				fout << endl;
			else
				fout << " ";
		}

		fout.close();
	}
}

void DataManager::SavePlayerInfo()
{
	shared_ptr<PlayerInfo> info = PLAYER->GetPlayerInfo();

	ofstream fout;
	fout.open("Data/SaveFiles/" + info->GetName() + "/PlayerInfo.txt");

	fout << info->GetName() << endl;
	fout << info->GetMaxHP() << " " << info->GetHP() << endl;
	fout << info->GetMaxStamina() << " " << info->GetStamina() << endl;
	Vector2 pos = info->GetPos();
	fout << pos.x << " " << pos.y;

	fout.close();

	fout.open("Data/SaveFiles/"+info->GetName() + "/PlayerItems.txt");

	vector<shared_ptr<GameObject>> items = info->GetItems();

	for (int i = 0; i < items.size(); i++)
	{
		fout << items[i]->GetCode() << " " << items[i]->GetCount() << endl;
	}

	fout.close();
}

void DataManager::LoadPlayerInfo(string playerName)
{
	int itemCode;
	int itemCount;
	short maxHp;
	short hp;
	short maxStamina;
	short stamina;
	Vector2 pos;
	vector<shared_ptr<GameObject>> items;
	
	ifstream fin;
	fin.open("Data/SaveFiles/"+playerName+"/PlayerInfo.txt");

	fin >> maxHp;
	fin >> hp;
	fin >> maxStamina;
	fin >> stamina;
	fin >> pos.x;
	fin >> pos.y;

	fin.close();

	fin.open("Data/SaveFiles/"+playerName+"/PlayerItems.txt");

	while (!fin.eof())
	{
		fin >> itemCode >> itemCount;
		items.push_back(ObjectSpawner::CreateObj(itemCode, itemCount));
	}

	fin.close();
}

void DataManager::LoadMap(string playerName, string mapName)
{
	ifstream fin;
	fin.open("Data/SaveFiles/" + playerName + "/" + mapName + ".txt");

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

		shared_ptr<Tile> info;
		int bitFlag = _tileInfos[tileCode]->GetBitFlag();
		if (bitFlag & TileInfo::Type::FARMING)
		{
			info = make_shared<ArableTile>(pos, tileCode, bitFlag, objectCode);
		}
		else if (bitFlag & TileInfo::Type::FISHING)
		{
			info = make_shared<FishableTile>(pos, tileCode, bitFlag, objectCode);
		}
		else
		{
			info = make_shared<Tile>(pos, tileCode, bitFlag, objectCode);
		}
		
		infos.push_back(info);

		x++;
		if (x == MAP_SIZE.x)
		{
			x = 0;
			y++;
		}
	}

	fin.close();

	if (infos.size() > 0)
		infos.pop_back();

	shared_ptr<MapInfo> mapInfo = make_shared<MapInfo>(mapName, size, infos);
	_mapInfos.push_back(mapInfo);
}



void DataManager::ReadMaps()
{
	ifstream fin;
	fin.open("Data/Contents/MapNames.txt");

	while (!fin.eof())
	{
		string name;
		fin >> name;
		_mapTable[name] = true;
	}

	fin.close();
}

void DataManager::ReadTileTypes()
{
	ifstream fin;
	fin.open("Data/Contents/TileTypes.txt");

	fin >> _tileMaxFrame.x;
	fin >> _tileMaxFrame.y;

	while (!fin.eof())
	{
		int type;
		fin >> type;

		shared_ptr<TileInfo> info = make_shared<TileInfo>(type);
		_tileInfos.push_back(info);
	}

	fin.close();
}

void DataManager::ReadObjectFile()
{
	ifstream fin;
	fin.open("Data/Contents/Object.txt");

	fin >> _objectMaxFrame.x;
	fin >> _objectMaxFrame.y;

	while (!fin.eof())
	{
		string name;
		vector<int> vals;

		fin >> name;
		for (int i = 0; i < 7; i++)
		{
			int tmp;
			fin >> tmp;
			vals.push_back(tmp);
		}
		shared_ptr<ObjectInfo> obj = make_shared<ObjectInfo>(name, vals);
		_objInfos.push_back(obj);
	}
	fin.close();
}

void DataManager::ReadPlayers()
{
	ifstream fin;
	fin.open("Data/Contents/PlayerNames.txt");

	while (!fin.eof())
	{
		string name;
		fin >> name;
		_playerTable[name] = true;
	}

	fin.close();
}


