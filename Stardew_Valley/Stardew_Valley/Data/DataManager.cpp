#include <atlstr.h>
#include "framework.h"
#include "../Object/Tile/TileType/ArableTile.h"
#include "../Object/Tile/TileType/FishableTile.h"
#include "../Framework/Utility/tinyxml2.h"
#include "DataManager.h"

DataManager* DataManager::_instance = nullptr;

DataManager::DataManager()
{
	ReadMaps();
	ReadXML();
	ReadTypes();
	ReadPlayers();
}

void DataManager::MapToolSave()
{
	ofstream fout;

	for (int i = 0; i < _mapInfos.size(); i++)
	{
		string mapName = _mapInfos[i]->GetName();
		Vector2 size = _mapInfos[i]->GetSize();
		vector<shared_ptr<Tile>> tileInfo = _mapInfos[i]->GetInfos();

		if (_mapTable.count(mapName) == false)
		{
			_mapTable[mapName] = true;

			fout.open("Data/Contents/MapNames.txt", std::ios::app);
			fout << endl << mapName;
			fout.close();
		}
		
		fout.open("Data/Contents/InitialMap/" + mapName + "Tile.txt");

		fout << size.x << " " << size.y << endl;

		for (int i = 0; i < tileInfo.size(); i++)
		{
			fout << tileInfo[i]->GetName();

			if (i + 1 == size.x * size.y)
				break;
			else if ((i + 1) % (int)size.x == 0)
				fout << endl;
			else
				fout << " ";
		}

		fout.close();

		fout.open("Data/Contents/InitialMap/" + mapName + "Obj.txt");

		for (int i = 0; i < tileInfo.size(); i++)
		{
			fout << tileInfo[i]->GetObjName();

			if (i + 1 == size.x * size.y)
				break;
			else if ((i + 1) % (int)size.x == 0)
				fout << endl;
			else
				fout << " ";
		}

		fout.close();
	}
}

void DataManager::PlaySave()
{
	/*CString path;
	TCHAR programPath[_MAX_PATH];
	GetModuleFileName(NULL, programPath, _MAX_PATH);
	GetCurrentDirectory(_MAX_PATH, programPath);
	path += programPath;
	path += L"/";
	path += PLAYER->GetPlayerInfo()->GetName().c_str();
	CreateDirectory(path, NULL);*/

	SaveMaps();
	SavePlayerInfo();
}


void DataManager::LoadInitialMaps()
{
	LoadMap("Data/Contents/InitialMap/", "Farming");
	LoadMap("Data/Contents/InitialMap/", "Fishing");
	LoadMap("Data/Contents/InitialMap/", "Dungeon");
	LoadMap("Data/Contents/InitialMap/", "Test");
	LoadMap("Data/Contents/InitialMap/", "Dungeon1");
	LoadMap("Data/Contents/InitialMap/", "Dungeon2");
	LoadMap("Data/Contents/InitialMap/", "Dungeon3");
}

void DataManager::LoadMaps(string name)
{
	LoadMap("Data/SaveFiles/" + name + "/", "Farming");
	LoadMap("Data/SaveFiles/" + name + "/", "Fishing");
	LoadMap("Data/SaveFiles/" + name + "/", "Dungeon");
	LoadMap("Data/SaveFiles/" + name + "/", "Test");
	LoadMap("Data/Contents/InitialMap/", "Dungeon1");
	LoadMap("Data/Contents/InitialMap/", "Dungeon2");
	LoadMap("Data/Contents/InitialMap/", "Dungeon3");
}

void DataManager::SaveMaps()
{
	string playerName = _playerInfo->GetName();
	ofstream fout;

	for (int i = 0; i < _mapInfos.size() - 3; i++)
	{
		string mapName = _mapInfos[i]->GetName();
		Vector2 size = _mapInfos[i]->GetSize();
		vector<shared_ptr<Tile>> tileInfo = _mapInfos[i]->GetInfos();

		if (_mapTable.count(mapName) == false)
		{
			_mapTable[mapName] = true;

			fout.open("Data/Contents/MapNames.txt", std::ios::app);
			fout << endl << mapName;
			fout.close();
		}

		fout.open("Data/SaveFiles/" + playerName + "/" + mapName + "Tile.txt");

		fout << size.x << " " << size.y << endl;

		for (int i = 0; i < tileInfo.size(); i++)
		{
			fout << tileInfo[i]->GetName();

			if (i + 1 != size.x * size.y)
				break;
			else if ((i + 1) % (int)size.x == 0)
				fout << endl;
			else
				fout << " ";
		}

		fout.close();

		fout.open("Data/SaveFiles/" + playerName + "/" + mapName + "Obj.txt");

		fout << size.x << " " << size.y << endl;

		for (int i = 0; i < tileInfo.size(); i++)
		{
			fout << tileInfo[i]->GetObjName();

			if (i + 1 != size.x * size.y)
				break;
			else if ((i + 1) % (int)size.x == 0)
				fout << endl;
			else
				fout << " ";
		}

		fout.close();
	}
}

void DataManager::SavePlayerInfo()
{
	/*ofstream fout;
	fout.open("Data/SaveFiles/" + _playerInfo->GetName() + "/PlayerInfo.txt");

	fout << _playerInfo->GetName() << endl;
	fout << _playerInfo->GetMaxHP() << " " << _playerInfo->GetHP() << endl;
	fout << _playerInfo->GetMaxStamina() << " " << _playerInfo->GetStamina() << endl;
	Vector2 pos = _playerInfo->GetCollider()->GetWorldPos();
	fout << pos.x << " " << pos.y;

	fout.close();

	fout.open("Data/SaveFiles/"+ _playerInfo->GetName() + "/PlayerItems.txt");

	vector<shared_ptr<GameObject>> items = _playerInfo->GetItems();

	for (int i = 0; i < items.size(); i++)
	{
		fout << items[i]->GetCode() << " " << items[i]->GetCount() << endl;
	}

	fout.close();*/
}

void DataManager::LoadPlayerInfo(string playerName)
{
	string itemName;
	string subName;
	vector<short> vals;
	short tmp;
	short tmp2;

	Vector2 pos;
	
	ifstream fin;
	fin.open("Data/SaveFiles/"+playerName+"/PlayerInfo.txt");

	fin >> tmp; //maxHp
	vals.push_back(tmp);

	fin >> tmp; //hp
	vals.push_back(tmp);


	fin >> tmp; //maxStamina
	vals.push_back(tmp);


	fin >> tmp; //stamina
	vals.push_back(tmp);


	fin >> tmp; //pos.x
	fin >> tmp2; //pos.y

	pos.x = tmp;
	pos.y = tmp2;

	fin.close();

	fin.open("Data/SaveFiles/"+playerName+"/PlayerItems.txt");


	vector<shared_ptr<Item>> items;

	for (int i = 0; i < 36; i++)
	{
		items.push_back(make_shared<Item>());
	}

	int index = 0;

	while (!fin.eof())
	{
		fin >> itemName >> tmp;
		items[index]->SetItem(itemName, tmp);
		index++;
	}

	fin.close();

	_playerInfo = make_shared<PlayerInfo>(playerName, vals, pos, items);
}

void DataManager::LoadMap(string path, string mapName)
{
	ifstream fin;
	fin.open(path + mapName + "Tile.txt");

	Vector2 size;
	fin >> size.x;
	fin >> size.y;

	vector<shared_ptr<Tile>> infos;

	string name;

	int x = 0;
	int y = 0;

	while (!fin.eof())
	{
		fin >> name;

		Vector2 pos = Vector2(TILE_SIZE.x * x, TILE_SIZE.y * y) + TILE_SIZE * 0.5f;

		shared_ptr<Tile> info;
		
		int bitFlag = _tileTable[name];

		if (bitFlag & TileType::FARMING)
		{
			info = make_shared<ArableTile>(name, pos);
		}
		else if (bitFlag & TileType::FISHING)
		{
			info = make_shared<FishableTile>(name, pos);
		}
		else
		{
			info = make_shared<Tile>(name, pos);
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

	fin.open(path + "Obj.txt");

	int index = 0;

	while (!fin.eof())
	{
		fin >> name;

		if (name != "BLANK" && name != "")
		{
			fin >> x >> y;

			OBJECT_SPAWNER->CreateObj(mapInfo, index, name, x, y);
		}
		index++;
	}

	fin.close();

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

void DataManager::ReadXML()
{
	string xmlPath = "Resource/XMLResource.xml";
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	string name;

	while (true)
	{
		if (row == nullptr)
			break;

		name = row->FindAttribute("n")->Value();

		if (_xmlTable.count(name) == 0)
		{
			_xmlTable[name] = make_shared<XMLInfo>(name);
		}

		XMLInfo::Position pos;
		Vector2 size;

		pos.x = row->FindAttribute("x")->IntValue();
		pos.y = row->FindAttribute("y")->IntValue();
		pos.w = row->FindAttribute("w")->IntValue();
		pos.h = row->FindAttribute("h")->IntValue();
		size.x = row->FindAttribute("s1")->FloatValue();
		size.y = row->FindAttribute("s2")->FloatValue();

		_xmlTable[name]->AddPosition(pos);
		_xmlTable[name]->AddSize(size);
		row = row->NextSiblingElement();
	}
}

void DataManager::ReadTypes()
{
	ifstream fin;

	//TileTable
	{
		fin.open("Data/Contents/TileTable.txt");

		string name;

		while (!fin.eof())
		{
			string name;
			fin >> name;
			int bitFlag;
			fin >> bitFlag;
			_tileTable[name] = bitFlag;
		}

		fin.close();
	}
	//DeployTable
	{
		fin.open("Data/Contents/DeployableTable.txt");
		string name;
		short type;
		short val;

		while (!fin.eof())
		{
			vector<short> vals;

			fin >> name;
			fin >> type;

			for (int i = 0; i < 3; i++)
			{
				fin >> val;
				vals.push_back(val);
			}

			_deployTable[name] = make_shared<DeployInfo>(type, vals);
		}

		fin.close();
	}
	//ItemTable
	{
		fin.open("Data/Contents/ItemTable.txt");
		string name;
		string deployName;
		short type;
		short price;
		short val;
		while (!fin.eof())
		{
			vector<short> vals;

			fin >> name;
			fin >> type;
			fin >> price;

			for (int i = 0; i < 4; i++)
			{
				fin >> val;
				vals.push_back(val);
			}

			fin >> deployName;

			_itemTable[name] = make_shared<ItemInfo>(deployName, type, price, vals);
		}

		fin.close();
	}
	// DropTable
	{
		fin.open("Data/Contents/DropTable.txt");
		string name;
		string dropItem;
		short percent;
		while (!fin.eof())
		{
			vector<short> vals;

			fin >> name;
			fin >> dropItem;
			fin >> percent;

			_dropTable[name] = make_shared<DropInfo>();
			_dropTable[name]->AddDatas(dropItem, percent);

			while (true)
			{
				fin >> dropItem;

				if (dropItem == "/")
					break;

				fin >> percent;

				_dropTable[name]->AddDatas(dropItem, percent);
			}
		}

		fin.close();
	}
	// FishTable
	{
		fin.open("Data/Contents/FishTable.txt");
		_fishTable.push_back(make_shared<FishInfo>());
		_fishTable.push_back(make_shared<FishInfo>());

		string name;
		short percent;
		int appearanceTime;

		while (!fin.eof())
		{
			fin >> name;
			fin >> percent;
			fin >> appearanceTime;

			_fishTable[appearanceTime]->AddFishInfo(name, percent); //float
		}

		fin.close();
	}
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


