#pragma once

class Tile;
class MapInfo;

class TileMap
{
public:
	TileMap(vector<shared_ptr<MapInfo>>& mapInfo);
	~TileMap() {}
	
	void Render();


	int GetWorldIndex(Vector2 pos);
	int GetCurrentMapIndex() { return _curMapIndex; }
	int GetFocusedIndex(Vector2 orginPos, Vector2 targetPos);
	vector<int> GetFocusedIndices(Vector2 originPos, Vector2 targetPos, short level);
	
	shared_ptr<Tile> GetWorldTile(Vector2 pos);
	shared_ptr<Tile> GetFocusedTile(Vector2 orginPos, Vector2 targetPos);
	
	vector<shared_ptr<MapInfo>>& GetMapInfos() { return _mapInfos; }
	shared_ptr<MapInfo> GetcurrentMapInfo() { return _mapInfos[_curMapIndex]; }

	void ChangeMap(int index);

	void Hoeing(Vector2 originPos, Vector2 targetPos, short level);
	void Watering(Vector2 originPos, Vector2 targetPos, short level);
	void Charging(Vector2 originPos, Vector2 tragetPos, short level);
	void Blocking(shared_ptr<RectCollider> col);
	void ChangeTile(Vector2 pos, int paletteIndex, string name);

	void SetMapInfo(vector<shared_ptr<MapInfo>> v) { _mapInfos = v; }

	vector<shared_ptr<TeleportInfo>> _teleports;

private:
	void SetCameraRange();
	void SetHoeDirt(int index);

	shared_ptr<Sprite> _renderer;
	shared_ptr<SingleColorRect> _focusRenderer;

	shared_ptr<RectCollider> _collider;
	shared_ptr<RectCollider> _collider2;
	vector<shared_ptr<MapInfo>>& _mapInfos;
	vector<shared_ptr<Tile>> _tiles;
	shared_ptr<LightPosBuffer> _lightPoses;
	shared_ptr<LightColorBuffer> _lightColors;
	unordered_map<string, int>& _tileInfos = DATA->GetTileInfos();

	string _curMapName;
	Vector2 _curMapSize;
	int _curMapIndex;
};

