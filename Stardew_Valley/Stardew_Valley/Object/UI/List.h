#pragma once
class List
{
public:
	List(Vector2 size, vector<shared_ptr<TextureButton>> buttons, Vector2 matrix);
	~List() {}

	void Render();
	void Update();

	void SetActive(bool val) { _isActive = val; }
	void SetParent(shared_ptr<Transform> trans) { _transform->SetParent(trans); }

	int GetCurIndex() { return _curIndex; }
	shared_ptr<Transform> GetTransform() { return _transform; }
private:
	void SetButtons();
	void PushButtonEvent(int index);

	void Scroll();

	Vector2 _size;
	Vector2 _buttonSize;
	Vector2 _matrix;

	shared_ptr<Transform> _transform;
	shared_ptr<SingleColorRect> _mainRect;
	vector<shared_ptr<TextureButton>> _buttons;

	int _curIndex = -1;
	bool _isActive;
};

