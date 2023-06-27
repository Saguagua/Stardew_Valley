#include "framework.h"
#include "Camera.h"
#include "../Utility/MathUtility.h"

Camera* Camera::_instance = nullptr;

Camera::Camera()
{
	_view = make_shared<Transform>();
	_proj = make_shared<MatrixBuffer>();

	//XMMATRIX projMatrix = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);
	XMMATRIX projMatrix = XMMatrixOrthographicLH(WIN_WIDTH, WIN_HEIGHT, 0.0f, 1.0f);
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

void Camera::PostRender()
{
}

void Camera::SetViewPort(UINT width, UINT height)
{
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

void Camera::FreeMode()
{
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
