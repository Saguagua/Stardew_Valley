#include <atlstr.h>
#include "framework.h"
#include "MapInfo.h"
#include "ObjectInfo.h"
#include "PlayerInfo.h"
#include "TileInfo.h"
#include "../Object/Tile/TileType/ArableTile.h"
#include "../Object/Tile/TileType/FishableTile.h"
#include "../Framework/Utility/tinyxml2.h"
#include "PlayerSubscribe.h"
#include "DataManager.h"

DataManager* DataManager::_instance = nullptr;

DataManager::DataManager()
{
	ReadMaps();
	ReadXML();
	ReadTypes();
	ReadPlayers();
}

shared_ptr<PlayerInfo> DataManager::RequestPlayerSubScribe(PlayerSubscribe* subscriber)
{
	_playerSubscribers.push_back(subscriber);

	return _playerInfo;
}

void DataManager::PlayerNotification(int type)
{
	for (int i = 0; i < _playerSubscribers.size(); i++)
	{
		if (_playerSubscribers[i]->_type == type)
			_playerSubscribers[i]->UpdateInfo();
	}
}

void DataManager::PlayerDeadNotification()
{
	for (int i = 0; i < _playerSubscribers.size(); i++)
		_playerSubscribers[i]->Dead();
}

void DataManager::AddMaxHP(short amount)
{
}

bool DataManager::AddHP(short amount)
{
	float maxHP = _playerInfo->GetMaxHP();
	float hp = _playerInfo->GetHP();

	hp += amount;

	if (hp <= 0)
		SetState(PlayerInfo::PlayerState::DEAD);

	float ratio = hp / maxHP;
	PlayerUI::GetInstance()->SetHP(ratio);
	_playerInfo->SetHP(hp);

	return !(_playerInfo->GetState() & PlayerInfo::PlayerState::DEAD);
}

void DataManager::AddMaxStamina(short amount)
{
}

bool DataManager::AddStamina(short amount)
{
	float maxStamina = _playerInfo->GetMaxStamina();
	float stamina = _playerInfo->GetStamina();

	stamina += amount;

	if (stamina <= 0)
		SetState(PlayerInfo::PlayerState::DEAD);

	float ratio = stamina / maxStamina;
	PlayerUI::GetInstance()->SetStamina(ratio);
	_playerInfo->SetStamina(stamina);

	return !(_playerInfo->GetState() & PlayerInfo::PlayerState::DEAD);
}

void DataManager::SetState(int state)
{
	_playerInfo->SetState(state);

	if (state & PlayerInfo::PlayerState::DEAD)
		PlayerDeadNotification();
}

shared_ptr<Item> DataManager::GetSelectedItem()
{
	return _playerInfo->GetItem(_playerInfo->GetSelectedIndex());
}

bool DataManager::AddItem(int type, string name)
{
	vector<shared_ptr<Item>>& items = _playerInfo->GetItems();

	for (auto item : items)
	{
		if (item->GetName() == name)
		{
			if (item->AddCount())
			{
				PlayerNotification(PlayerSubscribe::Type::ITEMS);
				return true;
			}
		}
	}

	for (int i = 0; i < items.size(); i++)
	{
		if (!items[i]->IsActive())
		{
			items[i] = ObjectSpawner::GetInstance()->CreateItem(name, type);
			PlayerNotification(PlayerSubscribe::Type::ITEMS);
			return true;
		}
	}

	return false;
}

void DataManager::SwapItems(int index1, int index2)
{
	vector<shared_ptr<Item>>& items = _playerInfo->GetItems();
	shared_ptr<Item> tmp = items[index1];
	items[index1] = items[index2];
	items[index2] = tmp;

	PlayerNotification(PlayerSubscribe::Type::ITEMS);
}

void DataManager::Save()
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
	string playerName = _playerInfo->GetName();
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

		fout.open("Data/SaveFiles/" + playerName + "/" + mapName + ".txt");

		fout << size.x << " " << size.y << endl;

		for (int i = 0; i < tileInfo.size(); i++)
		{
			/*fout << tileInfo[i]->GetTileCode() << " ";
			fout << tileInfo[i]->GetObjectCode();;*/

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
	short itemCount;
	short maxHp;
	short hp;
	short maxStamina;
	short stamina;

	Vector2 pos;
	vector<shared_ptr<Item>> items;
	
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
		fin >> itemName >> itemCount;
		items.push_back(ObjectSpawner::GetInstance()->CreateItem(itemName, itemCount));
	}

	fin.close();

	while (items.size() < 30)
	{
		items.push_back(ObjectSpawner::GetInstance()->CreateItem("BLANK", 0));
	}

	_playerInfo = make_shared<PlayerInfo>(playerName, maxHp, hp, maxStamina, stamina, items);
	_playerInfo->SetPos(pos);
	_playerInfo->GetCollider()->Update();
}

void DataManager::LoadMap(string playerName, string mapName)
{
	ifstream fin;
	fin.open("Data/SaveFiles/" + playerName + "/" + mapName + "Tile.txt");

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
		
		int bitFlag = _tileTable[name]->GetBitFlag();

		if (bitFlag & TileInfo::Type::FARMING)
		{
			info = make_shared<ArableTile>(name, pos);
		}
		else if (bitFlag & TileInfo::Type::FISHING)
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

	fin.open("Data/SaveFiles/" + playerName + "/" + mapName + "Obj.txt");

	int index = 0;

	while (!fin.eof())
	{
		fin >> name;

		if (name != "BLANK")
		{
			fin >> x >> y;

			ObjectSpawner::GetInstance()->CreateObj(mapInfo, index, name, x, y);
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
	string xmlPath = "Resource/Tile/Tiles.xml";
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

		pos.x = row->FindAttribute("x")->IntValue();
		pos.y = row->FindAttribute("y")->IntValue();
		pos.w = row->FindAttribute("w")->IntValue();
		pos.h = row->FindAttribute("h")->IntValue();

		_xmlTable[name]->AddPosition(pos);
	
		row = row->NextSiblingElement();
	}

	xmlPath = "Resource/Object/Objects.xml";
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

		pos.x = row->FindAttribute("x")->IntValue();
		pos.y = row->FindAttribute("y")->IntValue();
		pos.w = row->FindAttribute("w")->IntValue();
		pos.h = row->FindAttribute("h")->IntValue();

		_xmlTable[name]->AddPosition(pos);
		
		row = row->NextSiblingElement();
	}
}

void DataManager::ReadTypes()
{
	ifstream fin;
	fin.open("Data/Contents/TileProperty.txt");

	while (!fin.eof())
	{
		string name;
		fin >> name;
		int bitFlag;
		fin >> bitFlag;
		_tileTable[name] = make_shared<TileInfo>(bitFlag);
	}

	fin.close();

	fin.open("Data/Contents/DeployableTable.txt");

	string name;
	short type;
	short tmp;

	while (!fin.eof())
	{
		vector<short> vals;

		fin >> name;
		fin >> type;

		for (int i = 0; i < 3; i++)
		{
			fin >> tmp;
			vals.push_back(tmp);
		}

		_deployTable[name] = make_shared<DeployInfo>(type, vals);
	}

	fin.close();

	fin.open("Data/Contents/ItemTable.txt");
	short price;

	while (!fin.eof())
	{
		vector<short> vals;

		fin >> name;
		fin >> type;
		fin >> price;

		for (int i = 0; i < 4; i++)
		{
			fin >> tmp;
			vals.push_back(tmp);
		}

		_itemTable[name] = make_shared<ItemInfo>(type, price, vals);
	}

	fin.close();

	fin.open("Data/Contents/DropTable.txt");
	string dropItem;

	while (!fin.eof())
	{
		vector<short> vals;

		fin >> name;
		fin >> dropItem;
		fin >> tmp;

		_dropTable[name] = make_shared<DropInfo>();
		_dropTable[name]->AddDatas(dropItem, tmp);

		while (true)
		{
			fin >> dropItem;

			if (dropItem == "/")
				break;

			fin >> tmp;

			_dropTable[name]->AddDatas(dropItem, tmp);
		}
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


