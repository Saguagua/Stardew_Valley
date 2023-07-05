#pragma once
class Palette
{
public:
	Palette(Vector2 size);
	~Palette() {}

	void PostRender();
	void Update();

	void KeyInput();

	void Move();

private:
	shared_ptr<ColorButton> _mainWin;
	shared_ptr<List> _list;
	shared_ptr<ColorButton> _subWin;

	Vector2 _centerToMouse;

	Vector2 _size;

	vector<shared_ptr<TextureButton>> _buttons;
	vector<shared_ptr<TextureButton>> _tiles;

	vector<shared_ptr<TileInfo>> _infos;
};

