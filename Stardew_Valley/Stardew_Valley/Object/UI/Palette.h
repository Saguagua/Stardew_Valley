#pragma once
class Palette
{
public:
	Palette(Vector2 size);
	~Palette() {}

	void PostRender();
	void Update();

	void SetTileMap(shared_ptr<TileMap> tileMap) { _tileMap = tileMap; }

	shared_ptr<TileInfo> GetCurTileInfo();
	bool GetFocus() { return _onFocus; }

private:
	void CreateChartButtons();
	void CreateTileList();
	void CreateSaveList();

	//CallBack
	void OnFocus(bool val) { _onFocus = val; }
	void Move();
	void ChageChart(int index);

	shared_ptr<ColorButton> _mainRect;
	shared_ptr<List> _tileList;
	shared_ptr<List> _saveList;

	vector<shared_ptr<TextureButton>> _chartButtons;
	weak_ptr<TileMap> _tileMap;

	Vector2 _size;
	Vector2 _centerToMouse;

	int _chartIndex = 0;
	bool _onFocus = false;
};

