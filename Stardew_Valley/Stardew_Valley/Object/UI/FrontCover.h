#pragma once
class FrontCover
{
public:
	FrontCover();
	~FrontCover() {}

	void PostRender();
	void Update();

	void FadeStart(CallBack cb, CallBackInt cb2);
	bool IsActive() { return _isActive; }
private:
	shared_ptr<Transform> _transform;
	shared_ptr<SingleColorRect> _renderer;

	XMFLOAT4 _color = {0.0f, 0.0f, 0.0f, 0.0f};

	bool _darker = true;
	bool _isActive = false;

	float _timer;

	CallBack _cb;
	CallBackInt _cbInt;
};