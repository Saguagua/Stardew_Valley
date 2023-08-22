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
