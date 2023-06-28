#include "framework.h"
#include "../../Object/BagicObj/RectLine.h"
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

	//_rectCollider = make_shared<RectCollider>(Vector2(90, 150));
	//_rectCollider2 = make_shared<RectCollider>(Vector2(40, 70));

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

RectCollider::AABB_Info RectCollider::GetAABB_Info()
{
	AABB_Info info = {};

	Vector2 worldPos = _transform->GetWorldPos();

	info.Up = worldPos.y + _size.y;
	info.Down = worldPos.y - _size.y;
	info.right = worldPos.x + _size.x;
	info.left = worldPos.x - _size.x;

	return info;
}
