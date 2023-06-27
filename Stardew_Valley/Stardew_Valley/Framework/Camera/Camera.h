#pragma once
#include "../../Types.h"

class Camera
{
private:
	Camera()
	{
		_view = make_shared<Transform>();
		_proj = make_shared<MatrixBuffer>();

		XMMATRIX tmp = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);
		_proj->SetMatrix(tmp);
		_proj->Update();
	}
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

	void Update()
	{
		_view->Update();
		_view->Set_World(1);
		_proj->Set_VS(2);
	}


private:
	static Camera* _instance;

	shared_ptr<Transform> _view;
	shared_ptr<MatrixBuffer> _proj;

	weak_ptr<Transform> _target;

};

