#pragma once
#include "../../Types.h"

class Camera
{
private:
	Camera();
	~Camera() {}

public:

	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Camera();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Camera* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void Update();
	void PostRender();

	//void ShakeStart(float magnitude, float duration, float reduceDamping = 1.0f);

	void SetViewPort(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);

	void SetViewBuffer();
	void SetProjectionBuffer();

	void SetTarget(shared_ptr<Transform> target) { _target = target; }
	void SetLeftBottom(Vector2 value) { _leftBottom = value; }
	void SetRightTop(Vector2 value) { _rightTop = value; }
	void SetOffset(Vector2 value) { _offset = value; }

	void SetPos(Vector2 pos) { _view->SetPos(-pos); }
	void SetScale(Vector2 scale) { _view->SetScale(scale); }
	void SetAngle(float angle) { _view->SetAngle(-angle); }

	void AddPos(Vector2 pos) { _view->AddPos(-pos); }
	void AddScale(Vector2 scale) { _view->AddScale(-scale); }
	void AddAngle(float angle) { _view->AddAngle(-angle); }

	Vector2 GetWorldMousePos();

private:
	void FreeMode();
	void FollowMode();
	
	static Camera* _instance;

	shared_ptr<Transform> _view;
	shared_ptr<MatrixBuffer> _proj;

	float _speed;

	weak_ptr<Transform> _target;

	Vector2 _offset;

	Vector2 _leftBottom;
	Vector2 _rightTop;

	float _duration = 0.0f;
	float _magnitude = 0.0f;
	float _reduceDamping = 0.0f;

	Vector2 _originPos;
	Vector2 _winSize;
};

