#pragma once
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
	shared_ptr<class Crop> CreateCrop(string name, int progress, int quality);
	shared_ptr<Item> CreateItem(string objName, short count = 1);

	void Update();
	void Render();

	void SetPlayerInfo() { _playerInfo = DATA->GetPlayerInfo(); }

	void ActiveDropItem(string dropName, string itemName, Vector2 pos, int count);
private:
	static ObjectSpawner* _instance;

	unordered_map<string, shared_ptr<class DropInfo>> _dropTable;
	unordered_map<string, shared_ptr<class DeployInfo>> _deployTable;
	unordered_map<string, shared_ptr<class ItemInfo>> _itemTable;


	vector<shared_ptr<class DropItem>> _dropItems;
	vector<shared_ptr<class Crop>> _crops;

	shared_ptr<class PlayerInfo> _playerInfo;
	shared_ptr<LightTextureRect> _renderer;
};

