#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
:_size(size)
{
	_renderer = make_shared<RectLine>(_size);
	_type = Type::RECT;
}

void RectCollider::Render()
{
	_transform->Set_World(0);

	if (_isDebug)
		_renderer->Render();
}

bool RectCollider::IsCollision(Vector2 other)
{
	AABB_Info info = GetAABB_Info();

	if (other.x > info.left && other.x < info.right)
	{
		if (other.y > info.Down && other.y < info.Up)
			return true;
	}
	return false;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
	AABB_Info otherInfo = other->GetAABB_Info();
	AABB_Info myInfo = GetAABB_Info();

	if (otherInfo.right < myInfo.left)
		return false;
	if (otherInfo.left > myInfo.right)
		return false;
	if (otherInfo.Up < myInfo.Down)
		return false;
	if (otherInfo.Down > myInfo.Up)
		return false;

	return true;
}

bool RectCollider::OBB(shared_ptr<RectCollider> other)
{
	OBBRectInfo infoA = GetOBBInfo();
	OBBRectInfo infoB = other->GetOBBInfo();

	Vector2 aToB = infoB.worldPos - infoA.worldPos;

	// n : normal... 길이가 1인 벡터
	// e : edge... 모서리
	Vector2 nea1 = infoA.direction[0];
	Vector2 ea1 = infoA.direction[0] * infoA.length[0];
	Vector2 nea2 = infoA.direction[1];
	Vector2 ea2 = infoA.direction[1] * infoA.length[1];

	Vector2 neb1 = infoB.direction[0];
	Vector2 eb1 = infoB.direction[0] * infoB.length[0];
	Vector2 neb2 = infoB.direction[1];
	Vector2 eb2 = infoB.direction[1] * infoB.length[1];

	// nea1축으로 투영
	float length = abs(nea1.Dot(aToB));
	float lengthA = (ea1.Length());
	float lengthB = SeparateAxis(nea1, eb1, eb2);

	if (length > lengthA + lengthB)
		return false;

	// nea2축으로 투영
	length = abs(nea2.Dot(aToB));
	lengthA = (ea2.Length());
	lengthB = SeparateAxis(nea2, eb1, eb2);

	if (length > lengthA + lengthB)
		return false;

	// neb1축으로 투영
	length = abs(neb1.Dot(aToB));
	lengthA = SeparateAxis(neb1, ea1, ea2);
	lengthB = (eb1.Length());

	if (length > lengthA + lengthB)
		return false;

	// neb2축으로 투영
	length = abs(neb2.Dot(aToB));
	lengthA = SeparateAxis(neb2, ea1, ea2);
	lengthB = (eb2.Length());

	if (length > lengthA + lengthB)
		return false;

	return true;
}


RectCollider::OBBRectInfo RectCollider::GetOBBInfo()
{
	OBBRectInfo info;

	info.worldPos = _transform->GetWorldPos();

	XMFLOAT4X4 matrix;
	XMStoreFloat4x4(&matrix, _transform->GetSRT());

	info.direction[0] = { matrix._11, matrix._12 };
	info.direction[1] = { matrix._21, matrix._22 };

	info.direction[0] = info.direction[0].Normalize();
	info.direction[1] = info.direction[1].Normalize();

	Vector2 worldSize = GetWorldSize();

	info.length[0] = worldSize.x * 0.5f;
	info.length[1] = worldSize.y * 0.5f;

	return info;
}

Vector2 RectCollider::GetWorldSize()
{
	Vector2 scale = _transform->GetWorldScale();

	return Vector2(scale.x * _size.x, scale.y * _size.y);
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	AABB_Info myInfo = GetAABB_Info();
	Vector2 otherWorldCenter = other->GetWorldPos();
	float otherRadius = other->GetWorldRadius();

	float circleUp = otherWorldCenter.y + otherRadius;
	float circleDown = otherWorldCenter.y - otherRadius;
	float circleLeft = otherWorldCenter.x - otherRadius;
	float circleRight = otherWorldCenter.x + otherRadius;

	if (otherWorldCenter.x < myInfo.right && otherWorldCenter.x > myInfo.left)
	{
		if (circleDown < myInfo.Up && circleUp > myInfo.Down)
		{
			return true;
		}
	}

	if (otherWorldCenter.y > myInfo.Down && otherWorldCenter.y < myInfo.Up)
	{
		if (circleLeft < myInfo.right && circleRight > myInfo.left)
		{
			return true;
		}
	}

	if (other->IsCollision(Vector2(myInfo.left, myInfo.Up))
		|| other->IsCollision(Vector2(myInfo.right, myInfo.Up))
		|| other->IsCollision(Vector2(myInfo.left, myInfo.Down))
		|| other->IsCollision(Vector2(myInfo.right, myInfo.Down)))
	{
		return true;
	}

	return false;
}

bool RectCollider::Block(shared_ptr<CircleCollider> other)
{
	if (!IsCollision(other))
		return false;
	
	Vector2 myCenter = GetWorldPos();
	Vector2 otherCenter = other->GetWorldPos();
	Vector2 AtoB = otherCenter - myCenter;

	float otherRadius = other->GetWorldRadius();

	float yDistance = _size.y / 2 + otherRadius - abs(otherCenter.y - myCenter.y);
	float xDistance = _size.x / 2 + otherRadius - abs(otherCenter.x - myCenter.x);
	
	if (xDistance > yDistance)
	{
		AtoB.x = 0;
		Vector2 normal = AtoB.Normalize();
		Vector2 power = normal * yDistance;
		other->SetPos(other->GetTransform()->GetWorldPos() + power);
	}
	else
	{
		AtoB.y = 0;
		Vector2 normal = AtoB.Normalize();
		Vector2 power = normal * xDistance;
		other->SetPos(other->GetTransform()->GetWorldPos() + power);
	}

	return true;
}

bool RectCollider::Block(shared_ptr<RectCollider> other)
{
	if (!IsCollision(other))
		return false;

	Vector2 myCenter = GetWorldPos();
	Vector2 otherCenter = other->GetWorldPos();
	AABB_Info myAB = GetAABB_Info();
	AABB_Info otherAB = other->GetAABB_Info();

	AABB_Info infoA = GetAABB_Info();
	AABB_Info infoB = other->GetAABB_Info();

	Vector2 halfSizeA = Vector2(infoA.right - infoA.left, infoA.Up - infoA.Down) * 0.5f;
	Vector2 halfSizeB = Vector2(infoB.right - infoB.left, infoB.Up - infoB.Down) * 0.5f;

	Vector2 dir = other->GetWorldPos() - GetWorldPos();

	Vector2 overlap;
	overlap.x = (halfSizeA.x + halfSizeB.x) - abs(dir.x);
	overlap.y = (halfSizeA.y + halfSizeB.y) - abs(dir.y);

	if (overlap.y > overlap.x)
	{
		Vector2 temp = other->GetWorldPos();
		dir.y = 0;
		Vector2 normal = dir.Normalize();
		temp.x += normal.x * overlap.x;

		other->GetTransform()->SetPos(temp);
	}
	else
	{
		Vector2 temp = other->GetWorldPos();
		dir.x = 0;
		Vector2 normal = dir.Normalize();
		temp.y += normal.y * overlap.y;
		other->GetTransform()->SetPos(temp);
	}

	return true;
}

void RectCollider::SetSize(Vector2 size)
{
	Vector2 scale;
	scale.x = size.x / _size.x;
	scale.y = size.y / _size.y;
	_size = size;

	_transform->SetScale(scale);
}

RectCollider::AABB_Info RectCollider::GetAABB_Info()
{
	AABB_Info info = {};

	Vector2 worldPos = GetWorldPos();
	Vector2 halfSize = _size * 0.5f;

	info.Up = worldPos.y + halfSize.y;
	info.Down = worldPos.y - halfSize.y;
	info.right = worldPos.x + halfSize.x;
	info.left = worldPos.x - halfSize.x;

	return info;
}
