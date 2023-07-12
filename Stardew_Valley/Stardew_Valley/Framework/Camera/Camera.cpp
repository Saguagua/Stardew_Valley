#include "framework.h"
#include "Camera.h"
#include "../Utility/MathUtility.h"

Camera* Camera::_instance = nullptr;

Camera::Camera()
{
	_view = make_shared<Transform>();
	_postView = make_shared<MatrixBuffer>();
	_proj = make_shared<MatrixBuffer>();
	XMMATRIX projMatrix = XMMatrixOrthographicLH(WIN_WIDTH, WIN_HEIGHT, 0.0f, 1.0f);

	_view->SetPos(-CENTER);
	_view->Update();
	_postView->Update();
	
	_proj->SetMatrix(projMatrix);
	_proj->Update();
}

void Camera::Update()
{
	if (_target.expired())
		FreeMode();
	else
		FollowMode();

	_view->Update();
}

void Camera::SetPostViewPort()
{
	_postView->Set_VS(1);
}

void Camera::SetViewPort(UINT width, UINT height)
{
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	DC->RSSetViewports(1, &vp);
}

void Camera::SetViewBuffer()
{
	_view->Set_World(1);
}

void Camera::SetProjectionBuffer()
{
	_proj->Set_VS(2);
}

Vector2 Camera::GetWorldMousePos()
{
	XMMATRIX inverseMatrix = DirectX::XMMatrixInverse(nullptr, _view->GetSRT());

	Vector2 mousePos = MOUSE_POS - CENTER;
	return mousePos.TransformCoord(inverseMatrix);
}

Vector2 Camera::GetScreenMousePos()
{
	return MOUSE_POS - CENTER;
}

void Camera::FreeMode()
{
	if (KEY_PRESS('W'))
	{
		_view->AddPos(Vector2(0, -1) * DELTA_TIME * 220.0f);
	}
	if (KEY_PRESS('A'))
	{
		_view->AddPos(Vector2(1, 0) * DELTA_TIME * 220.0f);

	}
	if (KEY_PRESS('S'))
	{
		_view->AddPos(Vector2(0, 1) * DELTA_TIME * 220.0f);

	}
	if (KEY_PRESS('D'))
	{
		_view->AddPos(Vector2(-1, 0) * DELTA_TIME * 220.0f);
	}
}

void Camera::FollowMode()
{
	if (_target.expired())
		return;

	Vector2 targetPos = _target.lock()->GetWorldPos() - _offset;

	if (targetPos.x < _leftBottom.x)
		targetPos.x = _leftBottom.x;

	if (targetPos.x > _rightTop.x)
		targetPos.x = _rightTop.x;

	if (targetPos.y < _leftBottom.y)
		targetPos.y = _leftBottom.y;

	if (targetPos.y > _rightTop.y)
		targetPos.y = _rightTop.y;

	Vector2 tmp = -_view->GetWorldPos();
	Vector2 temp = Lerp(tmp, targetPos, 0.04f);

	SetPos(temp);
}
