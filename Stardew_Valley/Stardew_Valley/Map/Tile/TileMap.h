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
	void SetDebug(bool debug) { _colliders[0]->SetDebug(debug); }

	int GetWorldIndex(Vector2 pos);

private:
	void Play();
	void MouseInput();
	void Blocking();

	void ChangeTile();

	shared_ptr<TextureRect> _tileRenderer;
	shared_ptr<TextureRect> _objectRenderer;

	Vector2 _maxFrame;
	vector<shared_ptr<RectCollider>> _colliders;

	vector<int> _frameTypes;

	vector<shared_ptr<TileInfo>> _infos;

	weak_ptr<class Character> _player;
	weak_ptr<Palette> _palette;

	bool _isActive = false;

	string _mapName;
	Vector2 _mapSize;
};

