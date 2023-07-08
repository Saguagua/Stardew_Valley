#pragma once
class List
{
public:
	List(Vector2 size, wstring path, Vector2 frame);
	~List() {}

	void Render();
	void Update();
	void SetParent(shared_ptr<Transform> trans) { _mainRect->GetTransform()->SetParent(trans); }
	shared_ptr<TileInfo> GetCurTileInfo();
private:
	void CreateButtons(wstring path, Vector2 frame);
	void PushButtonEvent(int index);

	void Scroll();

	Vector2 _size;
	Vector2 _buttonSize;

	shared_ptr<ColorButton> _mainRect;
	vector<shared_ptr<TextureButton>> _buttons;
	vector<shared_ptr<TileInfo>> _infos;

	int _curIndex = -1;
};

