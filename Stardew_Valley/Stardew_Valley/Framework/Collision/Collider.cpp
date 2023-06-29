#include "framework.h"
#include "Collider.h"
#include "../../Object/BagicObj/ShapeLine.h"

void Collider::Update()
{
	_transform->Update();
}

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