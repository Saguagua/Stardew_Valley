#include "framework.h"
#include "Collider.h"

bool Collider::IsCollision(shared_ptr<Collider> other)
{
	switch (other->_type)
	{
	case Type::CIRCLE:
	{
		return IsCollision(dynamic_pointer_cast<class CircleCollider>(other));
	}
	case Type::RECT:
	{
		return IsCollision(dynamic_pointer_cast<class RectCollider>(other));
	}
	default:
		break;
	}

    return false;
}
