#pragma once
class Button
{
public:
	
	Button(Vector2 size);
	~Button() {}

	virtual void Render() abstract;
	virtual void PostRender() abstract;
	virtual void Update();

	void SetPushEvent(CallBack cb) { _pushEvent = cb; }
	void SetMouseOnEvent(CallBack cb) { _mouseOnEvent = cb; }

	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
protected:
	shared_ptr<RectCollider> _col;

	Vector2 _size;
	CallBack _pushEvent;
	CallBack _mouseOnEvent;
};

