#pragma once

class TileMap: public PlayerSubscribe
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
	int GetFocusedIndex();
	shared_ptr<class Tile> GetFocusedBlock();
	vector<shared_ptr<Tile>> GetFocusedBlocks(Vector2 point, short level);
	vector<int> GetFocusedIndices(Vector2 point, short level);
	vector<shared_ptr<class MapInfo>>& GetMapInfos() { return _mapInfos; }

	void ChangeMap(int index);

	virtual void UpdateInfo() override;
	virtual void Dead() override;

	void Hoeing(Vector2 point, short level);
	void Watering(Vector2 point, short level);
private:
	static TileMap* _instance;

	void SetCameraRange();
	void Play();
	void Blocking();

	void ChangeTile();

	void SetHoeDirt(int index);

	shared_ptr<class Sprite> _tileRenderer;
	shared_ptr<class Sprite> _objectRenderer;
	shared_ptr<SingleColorRect> _focusRenderer;

	vector<shared_ptr<RectCollider>> _colliders;

	vector<shared_ptr<MapInfo>>& _mapInfos = DATA->GetMapInfos();
	vector<shared_ptr<class Tile>> _tiles;
	unordered_map<string, int>& _tileInfos = DATA->GetTileInfos();

	string _curMapName;
	Vector2 _curMapSize;

};

