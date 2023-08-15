#pragma once

class TileMap: public PlayerSubscribe
{
	
public:
	TileMap();
	~TileMap() {}

	void Update();
	void Render();

	void SetDebug(bool debug) { _colliders[0]->SetDebug(debug); }

	int GetWorldIndex(Vector2 pos);
	shared_ptr<class Tile> GetMouseToPlayerIndex();
	vector<shared_ptr<class MapInfo>>& GetMapInfos() { return _mapInfos; }

	void ChangeMap(int index);

	virtual void UpdateInfo() override;
	virtual void Dead() override;
private:
	void SetCameraRange();
	void Play();
	void Blocking();

	void ChangeTile();

	shared_ptr<class Sprite> _tileRenderer;
	shared_ptr<class Sprite> _objectRenderer;

	vector<shared_ptr<RectCollider>> _colliders;

	vector<shared_ptr<MapInfo>> _mapInfos;
	vector<shared_ptr<class Tile>> _tiles;
	unordered_map<string, shared_ptr<TileInfo>>& _tileInfos = DATA->GetTileInfos();

	string _curMapName;
	Vector2 _curMapSize;

};

