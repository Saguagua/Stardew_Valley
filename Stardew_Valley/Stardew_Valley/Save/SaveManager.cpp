#include "framework.h"
#include "SaveManager.h"

SaveManager::SaveManager()
{
	ReadMaps();
	ReadTypes();
}

void SaveManager::SaveMap(string mapName, Vector2 size, vector<int> clips)
{
	if (_mapTable.count(mapName) == false)
	{
		_mapTable[mapName] = true;

		_fout.open("Map/Save/MapNames.txt", std::ios::app);
		_fout << mapName << endl;
		_fout.close();
	}

	_fout.open("Map/Save/" + mapName + ".txt");

	float max = size.x * size.y;

	for (int i = 0; i < max; i++)
	{
		_fout << clips[i] << endl;
	}

	_fout.close();

}

void SaveManager::LoadMap(string mapName)
{
}

void SaveManager::ReadMaps()
{
	_fin.open("Map/Save/MapNames.txt");

	_fin.close();
}

void SaveManager::ReadTypes()
{
	_fin.open("Map/Save/ClipTypes.txt");

	_fin.close();
}
