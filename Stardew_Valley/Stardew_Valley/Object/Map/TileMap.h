#pragma once

class TileMap
{
public:
	TileMap(wstring path, Vector2 size, Vector2 tileSize, shared_ptr<class Character> mainCharacter);
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
	shared_ptr<RectCollider> _col;
	shared_ptr<RectLine> _lineRenderer;
	weak_ptr<TextureRect> _tileRenderer;

	weak_ptr<Character> _mainCharacter;

	Vector2 _mapSize;
	Vector2 _tileSize;
	vector<vector<shared_ptr<TileInfo>>> _infos;

	bool _isActive = false;
	bool _isDebug = true;
};

