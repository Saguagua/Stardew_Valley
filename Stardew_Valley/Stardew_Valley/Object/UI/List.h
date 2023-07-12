#pragma once
class List
{
public:
	List(Vector2 size, vector<shared_ptr<TextureButton>> buttons, Vector2 frame);
	~List() {}

	void Render();
	void Update();

	void SetActive(bool val) { _isActive = val; }
	void SetParent(shared_ptr<Transform> trans) { _transform->SetParent(trans); }

	int GetCurIndex() { return _curIndex; }
	shared_ptr<Transform> GetTransform() { return _transform; }
private:
	void SetButtons(Vector2 frame);
	void PushButtonEvent(int index);

	void Scroll();

	Vector2 _size;
	Vector2 _buttonSize;

	shared_ptr<Transform> _transform;
	shared_ptr<SingleColorRect> _mainRect;
	vector<shared_ptr<TextureButton>> _buttons;
	vector<shared_ptr<TileInfo>> _infos;

	int _curIndex = -1;
	bool _isActive;
};

