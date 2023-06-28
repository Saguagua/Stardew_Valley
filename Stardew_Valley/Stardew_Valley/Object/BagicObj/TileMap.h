#pragma once

class TileMap
{
	enum Type
	{
		NONE,
		MOVEABLE,
		BLOCK
	};

	struct TileInfo
	{
		Vector2 centerPos = { 0,0 };
		Vector2 curClip = { 0,0 };
		TileMap::Type type = TileMap::Type::NONE;
	};

public:
	TileMap(Vector2 size, wstring path = L"");
	~TileMap() {}

	void Update();
	void Render();

private:
	void CreateTiles();


	shared_ptr<Transform> _transform;
	shared_ptr<class RectCollider> _tile;
	shared_ptr<Quad> _beachQuad;
	shared_ptr<Quad> _springOutdoorQuad;

	Vector2 _mapSize;
	Vector2 _tileSize;
	vector<vector<TileInfo>> _infos;
	
};

