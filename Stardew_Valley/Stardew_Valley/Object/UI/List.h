#pragma once
class List
{
public:
	List(Vector2 size, wstring path, Vector2 frame);
	~List() {}

	void Render();
	void Update();
	void KeyInput();
	void SetParent(shared_ptr<Transform> trans) { _mainRect->GetTransform()->SetParent(trans); }
private:
	void CreateButtons(wstring path, Vector2 frame);
	void PushButtonEvent(int index);

	Vector2 _size;
	Vector2 _curFrame;
	shared_ptr<ColorButton> _mainRect;
	vector<shared_ptr<TextureButton>> _buttons;

	int _curIndex = -1;
};

