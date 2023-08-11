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

	void CreateObj(string objName, int type, Vector2 pos);
	shared_ptr<class Crop> CreateCrop(string name, int progress, int quality);
	shared_ptr<GameObject> CreateItem(string objName, int type, short count = 1);

	void Update();
	void Render();

	void SetPlayerInfo() { _playerInfo = DATA->GetPlayerInfo(); }

	void ActiveDropItem(Vector2 pos, int objCode, int count);
private:

	static ObjectSpawner* _instance;
	unordered_map<string, shared_ptr<class ObjectInfo>> _objTable;

	vector<shared_ptr<class Crop>> _crops;
	vector<shared_ptr<PickableItem>> _pickObjs;
	vector<shared_ptr<BreakableItem>> _breakObjs;
	vector<shared_ptr<class DropItem>> _dropItems;

	shared_ptr<class PlayerInfo> _playerInfo;
	shared_ptr<LightTextureRect> _renderer;
};

