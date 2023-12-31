#pragma once
class Crop;
class PlayerImproved;
class FishingHook;

class ObjectSpawner
{
	ObjectSpawner();
	~ObjectSpawner() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new ObjectSpawner();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	
	static ObjectSpawner* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void CreateObj(shared_ptr<class MapInfo> map, int index, string objName, short val1, short val2);

	void DeleteObj(shared_ptr<class MapInfo> map, int index);
	
	void Update_Crops();
	void Update();
	void Render();

	void SetPlayer(shared_ptr<PlayerImproved> player);

	void ActiveDropItem(string name, Vector2 pos);
	void ActiveDropItem(string name, Vector2 pos, int count);

	void SpawnObjects(shared_ptr<class TileMap> map, int mapIndex, int objCount);
private:
	static ObjectSpawner* _instance;

	unordered_map<string, shared_ptr<DropInfo>>& _dropTable		= DATA->GetDropInfos();
	unordered_map<string, shared_ptr<DeployInfo>>& _deployTable	= DATA->GetDeployInfos();
	unordered_map<string, shared_ptr<ItemInfo>>& _itemTable		= DATA->GetItemInfos();
	unordered_map<string, shared_ptr<CropInfo>>& _cropTable		= DATA->GetCropInfos();

	vector<shared_ptr<class DropItem>> _dropItems;
	vector<shared_ptr<Crop>> _crops;
	vector<shared_ptr<DeployableObject>> _objs;

	shared_ptr<class PlayerInfo> _playerInfo = DATA->GetPlayerInfo();
	shared_ptr<Sprite> _renderer;

	weak_ptr<PlayerImproved> _player;
};