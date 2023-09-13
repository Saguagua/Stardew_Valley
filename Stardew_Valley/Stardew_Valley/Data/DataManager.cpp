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
	ReadTypes();
	ReadXML();
	ReadPlayers();
}

void DataManager::MapToolSave()
{
	ofstream fout;

	for (int i = 0; i < _initialMapInfos.size(); i++)
	{
		string mapName = _initialMapInfos[i]->GetName();
		Vector2 size = _initialMapInfos[i]->GetSize();
		vector<shared_ptr<Tile>> tileInfo = _initialMapInfos[i]->GetInfos();
		vector<shared_ptr<TeleportInfo>> teleports = _initialMapInfos[i]->GetTeleports();

		if (_mapTable.count(mapName) == false)
		{
			_mapTable[mapName] = true;

			fout.open("Data/Contents/MapNames.txt", std::ios::app);
			fout << endl << mapName;
			fout.close();
		}
		
		fout.open("Data/Contents/InitialMap/" + mapName + "Tile.txt");

		fout << size.x << " " << size.y << endl;

		for (int i = 0; i < teleports.size(); i++)
		{
			Vector2 colSize = teleports[i]->_collider->GetWorldSize();
			Vector2 worldPos = teleports[i]->_collider->GetWorldPos();

			fout << colSize.x / TILE_SIZE.x << " " << colSize.y / TILE_SIZE.y << " ";
			fout << worldPos.x << " " << worldPos.y << " ";
			fout << teleports[i]->_destination << " ";
			fout << teleports[i]->_where.x << " " << teleports[i]->_where.y << endl;
		}

		fout << -1 << endl;

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
			string name = tileInfo[i]->GetObjName();
			fout << name;


			if (name != "BLANK")
			{
				vector<int> val = tileInfo[i]->GetObj()->GetProperty();
				fout << " " << val[0] << " " << val[1];
			}

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
	_initialMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Farming"));
	_initialMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Fishing"));
	_initialMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Dungeon"));
	_initialMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Test"));
	_initialMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Dungeon1"));
	_initialMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Dungeon2"));
	_initialMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Dungeon3"));

	_initialMapInfos[0]->_sunOn = false;
	_initialMapInfos[1]->_sunOn = false;
	_initialMapInfos[2]->_sunOn = false;
	_initialMapInfos[3]->_sunOn = false;
	_initialMapInfos[4]->_sunOn = false;
	_initialMapInfos[5]->_sunOn = false;
	_initialMapInfos[6]->_sunOn = false;
}

void DataManager::LoadMaps(string name)
{
	_playerMapInfos.push_back(LoadMap("Data/SaveFiles/" + name + "/", "Farming"));
	_playerMapInfos.push_back(LoadMap("Data/SaveFiles/" + name + "/", "Fishing"));
	_playerMapInfos.push_back(LoadMap("Data/SaveFiles/" + name + "/", "Dungeon"));
	_playerMapInfos.push_back(LoadMap("Data/SaveFiles/" + name + "/", "Test"));
	_playerMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Dungeon1"));
	_playerMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Dungeon2"));
	_playerMapInfos.push_back(LoadMap("Data/Contents/InitialMap/", "Dungeon3"));

	_playerMapInfos[2]->_sunOn = false;
	_playerMapInfos[3]->_sunOn = false;
	_playerMapInfos[4]->_sunOn = false;
	_playerMapInfos[5]->_sunOn = false;
	_playerMapInfos[6]->_sunOn = false;
}

void DataManager::SaveMaps()
{
	string playerName = _playerInfo->GetName();
	ofstream fout;

	for (int i = 0; i < _playerMapInfos.size() - 3; i++)
	{
		string mapName = _playerMapInfos[i]->GetName();
		Vector2 size = _playerMapInfos[i]->GetSize();
		vector<shared_ptr<Tile>> tileInfo = _playerMapInfos[i]->GetInfos();

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

shared_ptr<MapInfo> DataManager::LoadMap(string path, string mapName)
{
	ifstream fin;
	fin.open(path + mapName + "Tile.txt");

	Vector2 size;
	fin >> size.x;
	fin >> size.y;

	vector<shared_ptr<TeleportInfo>> teleportInfos;
	Vector2 rectSize;
	Vector2 pos;
	int index = 0;
	Vector2 where;

	while (true)
	{
		fin >> rectSize.x;
		if (rectSize.x == -1)
			break;
		fin >> rectSize.y;
		rectSize.x *= TILE_SIZE.x;
		rectSize.y *= TILE_SIZE.y;

		fin >> pos.x;
		fin >> pos.y;
		fin >> index;
		fin >> where.x;
		fin >> where.y;
		auto teleport = make_shared<TeleportInfo>();
		teleport->_collider = make_shared<RectCollider>(rectSize);
		teleport->_collider->SetPos(pos);
		teleport->_collider->Update();

		teleport->_destination = index;
		teleport->_where = where;

		teleportInfos.push_back(teleport);
	}
	
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
		
		info->_mapIndex = x + y * size.x;
		infos.push_back(info);

		x++;

		if (x == size.x)
		{
			x = 0;
			y++;
		}
	}

	fin.close();

	shared_ptr<MapInfo> mapInfo = make_shared<MapInfo>(mapName, size, infos);
	mapInfo->SetTeleportInfo(teleportInfos);

	fin.open(path + mapName + "Obj.txt");

	index = 0;

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

	return mapInfo;
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
	string xmlPath = "Resource/XMLResource1.xml";
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
		_xmlTable[name]->SetPage(L"1");

		_xmlTable[name]->AddPosition(pos);
		_xmlTable[name]->AddSize(size);

		if (_deployTable.count(name) != 0)
			_deployTable[name]->SetSize(size);

		row = row->NextSiblingElement();
	}

	xmlPath = "Resource/XMLResource2.xml";
	document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	textureAtlas = document->FirstChildElement();
	row = textureAtlas->FirstChildElement();

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
		_xmlTable[name]->SetPage(L"2");

		if (_deployTable.count(name) != 0)
			_deployTable[name]->SetSize(size);

		row = row->NextSiblingElement();
	}

	xmlPath = "Resource/XMLResource3.xml";
	document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	textureAtlas = document->FirstChildElement();
	row = textureAtlas->FirstChildElement();

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
		int page;

		pos.x = row->FindAttribute("x")->IntValue();
		pos.y = row->FindAttribute("y")->IntValue();
		pos.w = row->FindAttribute("w")->IntValue();
		pos.h = row->FindAttribute("h")->IntValue();
		size.x = row->FindAttribute("s1")->FloatValue();
		size.y = row->FindAttribute("s2")->FloatValue();

		_xmlTable[name]->AddPosition(pos);
		_xmlTable[name]->AddSize(size);
		_xmlTable[name]->SetPage(L"3");

		if (_deployTable.count(name) != 0)
			_deployTable[name]->SetSize(size);

		row = row->NextSiblingElement();
	}

	xmlPath = "Resource/XMLResource4.xml";
	document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	textureAtlas = document->FirstChildElement();
	row = textureAtlas->FirstChildElement();

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
		_xmlTable[name]->SetPage(L"4");

		if (_deployTable.count(name) != 0)
			_deployTable[name]->SetSize(size);

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


