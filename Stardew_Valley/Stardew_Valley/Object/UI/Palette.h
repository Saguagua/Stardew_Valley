#pragma once
class Palette
{
public:
	Palette(Vector2 size);
	~Palette() {}

	void PostRender();
	void Update();

	void SetPos(Vector2 pos) { _mainRect->SetPos(pos); }
	void SetTileMap(shared_ptr<TileMap> tileMap) { _tileMap = tileMap; }

	Vector2 GetSize() { return _size; }
	Vector2 GetCurTileFrame();
	Vector2 GetCurObjectFrame();
	int GetIndex() { return _chartIndex; }
	bool GetFocus() { return _onFocus; }

private:
	void CreateChartButtons();
	void CreateTileList();
	void CreateObjectList();
	void CreateSaveList();

	//CallBack
	void OnFocus(bool val) { _onFocus = val; }
	void Move();
	void ChartButtonEvent(int index);
	void ChangeMap(bool chosen);

	vector<shared_ptr<MapInfo>> _mapInfos;
	shared_ptr<ColorButton> _mainRect;
	shared_ptr<List> _tileList;
	shared_ptr<List> _objectList;
	shared_ptr<List> _saveList;

	vector<shared_ptr<TextureButton>> _chartButtons;
	weak_ptr<TileMap> _tileMap;

	Vector2 _size;
	Vector2 _centerToMouse;
	Vector2 _tileMaxFrame;
	Vector2 _objectMaxFrame;

	int _chartIndex = 0;
	bool _onFocus = false;
};

