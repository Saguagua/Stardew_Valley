#pragma once
class Palette
{
public:
	Palette(Vector2 size);
	~Palette() {}

	void PostRender();
	void Update();

	void KeyInput();

private:
	shared_ptr<ColorButton> _mainRect;
	shared_ptr<ColorButton> _subRect;

	Vector2 _centerToMouse;

	Vector2 _size;

	shared_ptr<TextureRect> _tile;
};

