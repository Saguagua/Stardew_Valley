#include "framework.h"
#include "../../Object/BagicObj/CircleLine.h"
#include "CircleCollider.h"

bool CircleCollider::IsCollision(shared_ptr<class RectCollider> other)
{
	return false;
}

bool CircleCollider::IsCollision(shared_ptr<class CircleCollider> other)
{
	return false;
}
