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

bool RectCollider::IsCollision(shared_ptr<class RectCollider> other)
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

bool RectCollider::IsCollision(shared_ptr<class CircleCollider> other)
{
	AABB_Info myInfo = GetAABB_Info();
	Vector2 otherWorldPos = other->GetTransform()->GetWorldPos();
	float otherRadius = other->GetWorldRadius();

	float circleUp = otherWorldPos.y + otherRadius;
	float circleDown = otherWorldPos.y - otherRadius;
	float circleLeft = otherWorldPos.x - otherRadius;
	float circleRight = otherWorldPos.x + otherRadius;

	if (otherWorldPos.x < myInfo.right && otherWorldPos.x > myInfo.left)
	{
		if (circleDown < myInfo.Up && circleUp > myInfo.Down)
		{
			return true;
		}
	}

	if (otherWorldPos.y > myInfo.Down && otherWorldPos.y < myInfo.Up)
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
	
	Vector2 myPos = _transform->GetWorldPos();
	Vector2 otherPos = other->GetTransform()->GetWorldPos();
	Vector2 AtoB = otherPos - myPos;

	float otherRadius = other->GetWorldRadius();

	float yDistance = _size.y / 2 + otherRadius - abs(otherPos.y - myPos.y);
	float xDistance = _size.x / 2 + otherRadius - abs(otherPos.x - myPos.x);
	
	if (xDistance > yDistance)
	{
		AtoB.x = 0;
		Vector2 normal = AtoB.Normalize();
		Vector2 power = normal * yDistance;
		other->SetPos(otherPos + normal * yDistance);
	}
	else
	{
		AtoB.y = 0;
		Vector2 normal = AtoB.Normalize();
		Vector2 power = normal * xDistance;
		other->SetPos(otherPos + normal * xDistance);
	}


	return true;
}

RectCollider::AABB_Info RectCollider::GetAABB_Info()
{
	AABB_Info info = {};

	Vector2 worldPos = _transform->GetWorldPos();
	Vector2 halfSize = _size * 0.5f;
	info.Up = worldPos.y + halfSize.y;
	info.Down = worldPos.y - halfSize.y;
	info.right = worldPos.x + halfSize.x;
	info.left = worldPos.x - halfSize.x;

	return info;
}
