#pragma once

class TileMap
{
	enum Type
	{
		NONE,
		MOVEABLE = (1 << 0),
		BLOCK = (1 << 1),
		FARMING = (1 << 2),
		FISHING = (1 << 3)
	};

public:
	//todo : 파일을 읽어오는 생성자와 파일 없는 생성자 만들어야함
	TileMap(wstring path, Vector2 size, Vector2 tileSize, shared_ptr<class Character> mainCharacter);
	TileMap(Vector2 size);
	~TileMap() {}

	void Update();
	void Play();
	void CreateMap();

	void Render();

	void SetPalette(shared_ptr<class Palette> palette) { _palette = palette; }
	void SetCameraRange();
	void SetActive(bool active) { _isActive = active; }
	void SetDebug(bool debug) { _isActive = debug; }

	vector<Vector2>& GetFrames() { return _frames; }
	int GetWorldIndex(Vector2 pos);
	Vector2 GetWorldSize() { return Vector2(_mapSize.x * _tileSize.x, _mapSize.y * _tileSize.y); }

private:
	void CreateTileInfos();
	void ReadFile(wstring path);

	shared_ptr<Transform> _transform;
	shared_ptr<RectCollider> _col;
	shared_ptr<RectLine> _lineRenderer;
	weak_ptr<TextureRect> _tileRenderer;

	weak_ptr<Character> _mainCharacter;
	weak_ptr<Palette> _palette;

	Vector2 _mapSize;
	Vector2 _tileSize;

	vector<Vector2> _centers;
	vector<Vector2> _frames;

	vector<int> _frameTypes;

	bool _isActive = false;
	bool _isDebug = true;
};

