#pragma once
class Palette
{
	Palette(Vector2 size);
	~Palette() {}
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Palette(Vector2(450, 600));
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

	void PostRender();
	void Update();

	void SetPos(Vector2 pos) { _mainRect->SetPos(pos); }

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

	static Palette* _instance;

	vector<shared_ptr<class MapInfo>> _mapInfos;
	shared_ptr<ColorButton> _mainRect;
	shared_ptr<List> _tileList;
	shared_ptr<List> _objectList;
	shared_ptr<List> _saveList;

	vector<shared_ptr<TextureButton>> _chartButtons;

	Vector2 _size;
	Vector2 _centerToMouse;
	Vector2 _tileMaxFrame;
	Vector2 _objectMaxFrame;

	int _chartIndex = 0;
	bool _onFocus = false;
};

