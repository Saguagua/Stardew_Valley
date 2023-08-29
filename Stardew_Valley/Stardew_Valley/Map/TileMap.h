#pragma once

class TileMap
{

public:
	TileMap();
	~TileMap() {}
	
	void Update();
	void Render();

	void SetDebug(bool debug) { _collider->SetDebug(debug); }

	int GetWorldIndex(Vector2 pos);
	shared_ptr<Tile> GetWorldTile(Vector2 pos);
	int GetFocusedIndex(Vector2 orginPos, Vector2 targetPos);
	shared_ptr<class Tile> GetFocusedTile(Vector2 orginPos, Vector2 targetPos);
	vector<shared_ptr<Tile>> GetFocusedTiles(Vector2 point, short level);
	vector<int> GetFocusedIndices(Vector2 originPos, Vector2 targetPos, short level);
	vector<shared_ptr<class MapInfo>>& GetMapInfos() { return _mapInfos; }

	void ChangeMap(int index);

	void Hoeing(Vector2 originPos, Vector2 targetPos, short level);
	void Watering(Vector2 originPos, Vector2 targetPos, short level);
	void Charging(Vector2 originPos, Vector2 tragetPos, short level);
	void Blocking(shared_ptr<RectCollider> col);
	bool CanFishing(Vector2 pos);
private:
	void SetCameraRange();

	void ChangeTile();

	void SetHoeDirt(int index);

	shared_ptr<class Sprite> _renderer;
	shared_ptr<SingleColorRect> _focusRenderer;

	shared_ptr<RectCollider> _collider;

	vector<shared_ptr<MapInfo>>& _mapInfos = DATA->GetMapInfos();
	vector<shared_ptr<class Tile>> _tiles;
	unordered_map<string, int>& _tileInfos = DATA->GetTileInfos();

	string _curMapName;
	Vector2 _curMapSize;

};

