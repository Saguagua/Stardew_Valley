#pragma once

class TileMap
{
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
	shared_ptr<class Tile> GetMouseToPlayerIndex(Vector2 pos);
	vector<shared_ptr<MapInfo>>& GetMapInfos() { return _mapInfos; }

	void ChangeMap(int index);
private:
	void SetCameraRange();
	void Play();
	void Blocking();
	void Mouse();

	void ChangeTile();

	static TileMap* _instance;

	shared_ptr<LightTextureRect> _tileRenderer;
	shared_ptr<LightTextureRect> _objectRenderer;

	vector<shared_ptr<RectCollider>> _colliders;

	vector<shared_ptr<class MapInfo>> _mapInfos;
	vector<shared_ptr<class Tile>> _tiles;

	string _curMapName;
	Vector2 _curMapSize;
};

