#include "framework.h"
#include "Transform.h"
#include "../Render/ConstantBuffer.h"
#include "../Render/Buffers.h"

Transform::Transform()
{
	_buffer = make_shared<MatrixBuffer>();
}

void Transform::Update()
{
	Update_SRT();
	Update_VS();
}

void Transform::Update_VS()
{
	_buffer->SetMatrix(_srt);
	_buffer->Update();
	_buffer->Set_VS(0);
}

void Transform::Update_SRT()
{
	_scaleM = XMMatrixScaling(_scale.x, _scale.y, 1);
	XMMATRIX rotate = XMMatrixRotationZ(_angle);
	XMMATRIX pos = XMMatrixTranslation(_pos.x, _pos.y, 0);

	_srt = _scaleM * rotate * pos;

	if (!_parent.expired())
		_srt *= _parent.lock()->GetSRT();
}

void Transform::Set_World(UINT slot)
{
	_buffer->Set_VS(slot);
}

Vector2 Transform::GetWorldPos()
{
	XMFLOAT4X4 tmp;
	XMStoreFloat4x4(&tmp, _srt);

	return Vector2(tmp._41, tmp._42);
}

Vector2 Transform::GetWorldScale()
{
	XMFLOAT4X4 tmp;
	XMStoreFloat4x4(&tmp, _scaleM);

	if (!_parent.expired())
	{
		Vector2 pos = _parent.lock()->GetWorldScale();
		return Vector2(pos.x * tmp._11, pos.y * tmp._22);
	}

	return Vector2(tmp._11, tmp._22);
}
