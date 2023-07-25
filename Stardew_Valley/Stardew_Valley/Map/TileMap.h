#pragma once

class TileMap
{
	enum Type
	{
		NONE,
		MOVEABLE = (1 << 0),
		BLOCK = (1 << 1),
		FARMING = (1 << 2),
		FISHING = (1 << 3)
	};

	TileMap();
	~TileMap() {}
public:

	static void Create()
	{
		if (_instance == nullptr)
			_instance = new TileMap();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static TileMap* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void Update();
	void Render();

	void SetDebug(bool debug) { _colliders[0]->SetDebug(debug); }

	int GetWorldIndex(Vector2 pos);
	int GetMouseToPlayerIndex(Vector2 pos);
	vector<shared_ptr<class MapInfo>>& GetMapInfo() { return _mapInfos; }

	void ChangeMap(int index);
private:
	void SetCameraRange();
	void Play();
	void Blocking();
	void Mouse();

	void ChangeTile();

	static TileMap* _instance;

	shared_ptr<TextureRect> _tileRenderer;
	shared_ptr<TextureRect> _objectRenderer;

	Vector2 _tileMaxFrame;
	Vector2 _objectMaxFrame;
	vector<int> _frameTypes;

	vector<shared_ptr<RectCollider>> _colliders;

	vector<shared_ptr<class MapInfo>> _mapInfos;

	string _mapName;
	Vector2 _mapSize;
	vector<shared_ptr<class TileInfo>> _tileInfos;
};

