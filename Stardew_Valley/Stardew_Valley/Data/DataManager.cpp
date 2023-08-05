#include <atlstr.h>
#include "framework.h"
#include "MapInfo.h"
#include "ObjectInfo.h"
#include "PlayerInfo.h"
#include "TileInfo.h"
#include "../Object/Tile/TileType/ArableTile.h"
#include "../Object/Tile/TileType/FishableTile.h"
#include "PlayerSubscribe.h"
#include "DataManager.h"

DataManager* DataManager::_instance = nullptr;

DataManager::DataManager()
{
	ReadMaps();
	ReadTileTypes();
	ReadObjectFile();
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

shared_ptr<GameObject> DataManager::GetSelectedItem()
{
	return _playerInfo->GetItem(_playerInfo->GetSelectedIndex());
}

bool DataManager::AddItem(int objCode)
{
	return false;
}

void DataManager::SwapItems(int index1, int index2)
{
	vector<shared_ptr<GameObject>>& items = _playerInfo->GetItems();
	shared_ptr<GameObject> tmp = items[index1];
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
	ofstream fout;
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

	_playerInfo = make_shared<PlayerInfo>(playerName, maxHp, hp, maxStamina, stamina, items);
	_playerInfo->SetPos(pos);
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
		vector<short> vals;

		fin >> name;
		for (int i = 0; i < 8; i++)
		{
			short tmp;
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


