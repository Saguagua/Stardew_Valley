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

	static shared_ptr<GameObject> CreateObj(int itemCode, short count = 1);
	
	void Update();
	void Render();

	void ActiveDropItem(Vector2 pos, int itemCode, int count);
private:
	static ObjectSpawner* _instance;
	vector<shared_ptr<class DropItem>> _dropItems;
	shared_ptr<TextureRect> _renderer;
};

