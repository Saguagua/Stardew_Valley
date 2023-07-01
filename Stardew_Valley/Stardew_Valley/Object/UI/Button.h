#pragma once
class Button
{
public:
	
	Button(Vector2 size, CallBack callback);
	~Button() {}

	virtual void Render() abstract;
	virtual void PostRender() abstract;
	virtual void Update();

	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }
protected:
	shared_ptr<RectCollider> _col;

	Vector2 _size;
	CallBack _callback;
};

