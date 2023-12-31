#pragma once
class List
{
public:
	List(Vector2 size, Vector2 matrix, vector<string> names);
	List(Vector2 matrix) : _matrix(matrix) {}
	virtual ~List() {}

	void Render();
	void Update();

	void SetActive(bool val) { _isActive = val; }
	void SetParent(shared_ptr<Transform> trans) { _transform->SetParent(trans); }
	void SetPos(Vector2 pos) { _transform->SetPos(pos); }

	void AddCallBack(vector<CallBack> cbs);
	void AddCallBackInt(vector<CallBackInt> cbs);

	int GetCurIndex() { return _curIndex; }
	shared_ptr<TextureButton> GetCurBotton() { return _buttons[_curIndex]; }
	shared_ptr<Transform> GetTransform() { return _transform; }

protected:
	void CreateButtons(vector<string> names);

	void SetButtons(Vector2 startPos, Vector2 space);
	void PushButtonEvent(int index);

	void Scroll();

	Vector2 _size;
	Vector2 _buttonSize;
	Vector2 _matrix;

	shared_ptr<Transform> _transform;
	shared_ptr <Sprite> _body;
	vector<shared_ptr<TextureButton>> _buttons;

	int _curIndex = 0;
	bool _isActive = false;

};

