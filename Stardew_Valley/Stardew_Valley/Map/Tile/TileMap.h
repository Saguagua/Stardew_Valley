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
	TileMap(shared_ptr<class MapInfo> mapInfo);
	TileMap();
	~TileMap() {}

	void Update();
	void Render();

	void LoadMap(shared_ptr<MapInfo> info);

	void SetCameraRange();
	void SetPlayer(shared_ptr<class Character> player) { _player = player; }
	void SetPalette(shared_ptr<class Palette> palette) { _palette = palette; }
	void SetActive(bool active) { _isActive = active; }
	void SetDebug(bool debug) { _isDebug = debug; }

	vector<Vector2>& GetFrames() { return _frames; }
	int GetWorldIndex(Vector2 pos);

private:
	void Play();
	void MouseInput();
	void KeyInput();
	void Blocking();

	void ChangeTile();

	vector<shared_ptr<RectCollider>> _colliders;
	shared_ptr<RectLine> _lineRenderer;
	shared_ptr<TextureRect> _tileRenderer;

	weak_ptr<class Character> _player;
	weak_ptr<Palette> _palette;

	vector<Vector2> _centers;

	vector<Vector2> _frames;
	Vector2 _maxFrame;
	vector<int> _frameTypes;

	bool _isActive = false;
	bool _isDebug = false;

	string _mapName;
	Vector2 _mapSize;
};

