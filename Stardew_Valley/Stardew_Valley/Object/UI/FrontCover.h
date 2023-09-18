#pragma once
class FrontCover
{
public:
	FrontCover();
	~FrontCover() {}

	void PostRender();
	void Update();

	void SetCallBack(CallBack cb) { _cb = cb; }

	bool _isActive = false;
private:
	shared_ptr<Transform> _transform;
	shared_ptr<SingleColorRect> _renderer;

	XMFLOAT4 _color = {0.0f, 0.0f, 0.0f, 0.0f};

	bool _darker = true;

	CallBack _cb;
};