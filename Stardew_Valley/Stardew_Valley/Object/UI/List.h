#pragma once
class List
{
public:
	List(wstring path, Vector2 size, Vector2 matrix, int count);
	List(Vector2 matrix) : _matrix(matrix) {}
	~List() {}

	void Render();
	virtual void Update();

	void SetActive(bool val) { _isActive = val; }
	void SetParent(shared_ptr<Transform> trans) { _transform->SetParent(trans); }
	void SetPos(Vector2 pos) { _transform->SetPos(pos); }
	void AddCallBack(vector<CallBack> cbs);
	void AddCallBackInt(vector<CallBackInt> cbs);

	int GetCurIndex() { return _curIndex; }
	shared_ptr<Transform> GetTransform() { return _transform; }

protected:
	virtual void CreateButtons(wstring path, int count);
	virtual void SetButtons(Vector2 startPos, Vector2 space);
	virtual void PushButtonEvent(int index);

	void Scroll();

	Vector2 _size;
	Vector2 _buttonSize;
	Vector2 _matrix;

	shared_ptr<Transform> _transform;
	shared_ptr <class  XMLRect > _body;
	vector<shared_ptr<TextureButton>> _buttons;

	int _curIndex = -1;
	bool _isActive = false;
};

