#pragma once
class Crop;

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

	shared_ptr<DeployableObject> CreateObj(string objName);
	void CreateObj(shared_ptr<class MapInfo> map, int index, string objName, short val1, short val2);
	Crop* CreateCrop(string name, short progress = 0, short quality = 2, short level = 0);
	
	void Update_Crops();
	void Update();
	void Render();

	void SetPlayerInfo() { _playerInfo = DATA->GetPlayerInfo(); }

	void ActiveDropItem(string dropName, string itemName, Vector2 pos, int count);
private:
	static ObjectSpawner* _instance;

	unordered_map<string, shared_ptr<DropInfo>>& _dropTable		= DATA->GetDropInfos();
	unordered_map<string, shared_ptr<DeployInfo>>& _deployTable	= DATA->GetDeployInfos();
	unordered_map<string, shared_ptr<ItemInfo>>& _itemTable		= DATA->GetItemInfos();
	unordered_map<string, shared_ptr<CropInfo>>& _cropTable		= DATA->GetCropInfos();

	vector<shared_ptr<class DropItem>> _dropItems;
	list<Crop*> _crops;

	shared_ptr<class PlayerInfo> _playerInfo = DATA->GetPlayerInfo();
	shared_ptr<Sprite> _renderer;
};