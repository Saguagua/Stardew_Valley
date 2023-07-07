#pragma once
class Button
{
public:
	
	Button(Vector2 size);
	~Button() {}

	virtual void Render() abstract;
	virtual void Update();

	void SetPushEvent(CallBack cb) { _pushEvent = cb; }
	void SetPushEvent(CallBackInt cb) { _pushIntEvent = cb; }

	void SetScrollEvent(CallBack cb) { _scrollEvent = cb; }
	void SetScrollEvent(CallBackInt cb) { _scrollIntEvent = cb; }

	void SetMouseOnEvent(CallBack cb) { _mouseOnEvent = cb; }
	void SetMouseOnEvent(CallBackInt cb) { _mouseOnIntEvent = cb; }

	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
protected:
	shared_ptr<RectCollider> _col;

	Vector2 _size;
	CallBack _pushEvent;
	CallBackInt _pushIntEvent;
	CallBack _mouseOnEvent;
	CallBackInt _mouseOnIntEvent;
	CallBack _scrollEvent;
	CallBackInt _scrollIntEvent;
};

