#include "framework.h"
#include "../../Object/BagicObj/RectLine.h"
#include "RectCollider.h"

bool RectCollider::IsCollision(shared_ptr<class RectCollider> other)
{
	return false;
}

bool RectCollider::IsCollision(shared_ptr<class CircleCollider> other)
{
	return false;
}
