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

	TileMap(Vector2 size, wstring path, shared_ptr<class Character> mainCharacter);
	~TileMap() {}

	void Update();
	void Render();

	void SetCameraRange();
	void SetActive(bool active) { _isActive = active; }
	void SetDebug(bool debug) { _isActive = debug; }

	vector<vector<shared_ptr<TileInfo>>>& GetInfo() { return _infos; }
	Vector2 GetWorldIndex(Vector2 pos);
	Vector2 GetWorldSize() { return Vector2(_mapSize.x * _tileSize.x, _mapSize.y * _tileSize.y); }

private:
	void CreateTiles();

	shared_ptr<Transform> _transform;
	shared_ptr<class RectLine> _lineRenderer;
	shared_ptr<Quad> _quad;
	weak_ptr<class Character> _mainCharacter;

	Vector2 _mapSize;
	Vector2 _tileSize;
	vector<vector<shared_ptr<TileInfo>>> _infos;

	bool _isActive = false;
	bool _isDebug = false;
};

