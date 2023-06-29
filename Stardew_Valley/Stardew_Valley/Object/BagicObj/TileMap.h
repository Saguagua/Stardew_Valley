#pragma once

class TileMap
{
	enum Type
	{
		NONE,
		MOVEABLE,
		BLOCK
	};

	
public:

	struct TileInfo
	{
		TileInfo(Vector2 centerPos, Vector2 curClip, TileMap::Type type)
		{
			this->centerPos = centerPos;
			this->curClip = curClip;
			this->type = type;
		}
		Vector2 centerPos = { 0,0 };
		Vector2 curClip = { 0,0 };
		TileMap::Type type = TileMap::Type::NONE;
	};

	TileMap(Vector2 size, wstring path = L"");
	~TileMap() {}

	void Update();
	void Render();

	vector<vector<shared_ptr<TileInfo>>>& GetInfo() { return _infos; }

	Vector2 GetWorldIndex(Vector2 pos);

private:
	void CreateTiles();

	shared_ptr<Transform> _transform;
	shared_ptr<class RectCollider> _tile;
	shared_ptr<Quad> _beachQuad;
	shared_ptr<Quad> _springOutdoorQuad;

	Vector2 _mapSize;
	Vector2 _tileSize;
	vector<vector<shared_ptr<TileInfo>>> _infos;
};

