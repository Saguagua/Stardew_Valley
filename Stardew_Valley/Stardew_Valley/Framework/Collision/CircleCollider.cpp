#include "framework.h"
#include "../../Object/BagicObj/CircleLine.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
:_radius(radius)
{
	_renderer = make_shared<CircleLine>(_radius);
	_type = Type::CIRCLE;
}

void CircleCollider::Render()
{
	_transform->Set_World(0);
	_renderer->Render();
}

bool CircleCollider::IsCollision(shared_ptr<class RectCollider> other)
{
	return false;
}

bool CircleCollider::IsCollision(shared_ptr<class CircleCollider> other)
{
	return false;
}