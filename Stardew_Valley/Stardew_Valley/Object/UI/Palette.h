#pragma once
class MapInfo;

class Palette
{
	enum ChartType
	{
		TILE,
		OBJECT,
		LOAD,
		SAVE
	};

	Palette(Vector2 size);
	~Palette() {}
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Palette(Vector2(350, 500));
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Palette* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void Render();
	void PostRender();
	void Update();

	void SetPos(Vector2 pos) { _mainRect->SetPos(pos); }

	Vector2 GetSize() { return _size; }
	int GetIndex() { return _chartIndex; }
	bool GetFocus() { return _onFocus; }

private:
	void CreateChartButtons();
	void CreateTileList();
	void CreateObjectList();
	void CreateLoadList();

	void KeyInput();

	//CallBack
	void OnFocus(bool val) { _onFocus = val; }
	void Move();
	void ChartButtonEvent(int index);
	void ChangeMap(int index);

	static Palette* _instance;

	shared_ptr<TileMap> _map;

	vector<shared_ptr<MapInfo>> _mapInfos;
	shared_ptr<ColorButton> _mainRect;
	vector<shared_ptr<List>> _lists;

	vector<shared_ptr<TextureButton>> _chartButtons;

	Vector2 _size;
	Vector2 _centerToMouse;

	int _chartIndex = ChartType::TILE;
	bool _onFocus = false;
};

