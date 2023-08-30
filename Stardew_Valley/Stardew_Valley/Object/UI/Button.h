#pragma once
class Button
{
public:
	
	Button(Vector2 size);
	virtual ~Button() {}

	virtual void Render() abstract;
	virtual void Update();

	void SetDebug(bool val) { _col->SetDebug(val); }
	void SetPos(Vector2 pos) { _col->SetPos(pos); }

	void SetLineColor(XMFLOAT4 color) { _col->SetColor(color); }

	void AddPushEvent(CallBack cb) { _pushEvents.push_back(cb); }
	void AddPushEvent(CallBackInt cb) { _pushIntEvents.push_back(cb); }
	void SetPushEvent(CallBackBool cb) { _pushBoolEvent = cb; }

	void SetScrollEvent(CallBack cb) { _scrollEvent = cb; }
	void SetScrollEvent(CallBackInt cb) { _scrollIntEvent = cb; }

	void SetMouseOnEvent(CallBack cb) { _onEvent = cb; }
	void SetMouseOnEvent(CallBackInt cb) { _onIntEvent = cb; }
	void SetMouseOnEvent(CallBackBool cb) { _onBoolEvent = cb; }

	bool GetFocus() { return _onFocus; }
	Vector2 GetSize() { return _size; }
	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }

protected:
	shared_ptr<RectCollider> _col;

	Vector2 _size;

	CallBack _onEvent;
	CallBackInt _onIntEvent;
	CallBackBool _onBoolEvent;

	CallBack _scrollEvent;
	CallBackInt _scrollIntEvent;

	vector<CallBack> _pushEvents;
	CallBackBool _pushBoolEvent;
	vector<CallBackInt> _pushIntEvents;

	bool _onFocus = false;
};

