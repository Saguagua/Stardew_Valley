#pragma once

class TileMap: public PlayerSubscribe
{
	
public:
	TileMap();
	~TileMap() {}

	void Update();
	void Render();

	void SetDebug(bool debug) { _colliders[0]->SetDebug(debug); }

	int GetWorldIndex(Vector2 pos);
	shared_ptr<class Tile> GetMouseToPlayerIndex();
	vector<shared_ptr<MapInfo>>& GetMapInfos() { return _mapInfos; }

	void ChangeMap(int index);

	virtual void UpdateInfo() override;
	virtual void Dead() override;
private:
	void SetCameraRange();
	void Play();
	void Blocking();
	void Mouse();

	void ChangeTile();


	shared_ptr<LightTextureRect> _tileRenderer;
	shared_ptr<LightTextureRect> _objectRenderer;

	vector<shared_ptr<RectCollider>> _colliders;

	vector<shared_ptr<class MapInfo>> _mapInfos;
	vector<shared_ptr<class Tile>> _tiles;

	string _curMapName;
	Vector2 _curMapSize;

};

