#pragma once
class Palette
{
public:
	Palette(Vector2 size);
	~Palette() {}

	void PostRender();
	void Update();

	shared_ptr<TileInfo> GetCurTileInfo() { return _tileList->GetCurTileInfo(); }
	bool GetFocus() { return _onFocus; }
private:
	void CreateChartButtons();

	void OnFocus(bool val) { _onFocus = val; }
	void Move();
	void ChageChart(int index);

	shared_ptr<ColorButton> _mainWin;
	shared_ptr<List> _tileList;
	vector<shared_ptr<TextureButton>> _chartButtons;
	vector<shared_ptr<TextureButton>> _tiles;
	vector<shared_ptr<TileInfo>> _infos;

	Vector2 _size;
	Vector2 _centerToMouse;

	int _chartIndex = 0;

	bool _onFocus = false;
};

