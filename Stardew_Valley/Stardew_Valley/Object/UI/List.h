#pragma once
class List
{
public:
	List(Vector2 matrix) : _matrix(matrix) {}
	~List() {}

	void Render();
	virtual void Update();

	void SetActive(bool val) { _isActive = val; }
	void SetParent(shared_ptr<Transform> trans) { _transform->SetParent(trans); }
	void SetPos(Vector2 pos) { _transform->SetPos(pos); }

	int GetCurIndex() { return _curIndex; }
	shared_ptr<Transform> GetTransform() { return _transform; }

protected:
	virtual void CreateButtons() abstract;
	virtual void SetButtons(Vector2 startPos, Vector2 space);
	virtual void PushButtonEvent(int index);

	void Scroll();

	Vector2 _size;
	Vector2 _buttonSize;
	Vector2 _matrix;

	shared_ptr<Transform> _transform;
	shared_ptr<SingleColorRect> _mainRect;
	shared_ptr<TextureRect> _backGround;
	shared_ptr <class  XMLRect > _body;
	vector<shared_ptr<TextureButton>> _buttons;

	int _curIndex = -1;
	bool _isActive;
};

