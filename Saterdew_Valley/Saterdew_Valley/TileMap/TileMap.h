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
	TileMap(Vector2 size, wstring path = L"");
	~TileMap() {}

	void Update();
	void Render();

private:
	void CreateTiles();

	shared_ptr<Transform> _transform;
	shared_ptr<class Tile> _tile;

	Vector2 _mapSize;
	Vector2 _tileSize;
	vector<vector<Type>> _types;
	
};

