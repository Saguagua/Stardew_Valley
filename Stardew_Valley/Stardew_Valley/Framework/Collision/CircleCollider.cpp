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

bool CircleCollider::IsCollision(Vector2 other)
{
	Vector2 pos = _transform->GetWorldPos();
	float length = (other - pos).Length();
	float worldRadius = GetWorldRadius();

	return length < worldRadius* worldRadius;
}

bool CircleCollider::IsCollision(shared_ptr<class RectCollider> other)
{
	return other->IsCollision(shared_from_this());
}

bool CircleCollider::IsCollision(shared_ptr<class CircleCollider> other)
{
	float radiusLength = (GetWorldRadius() + other->GetWorldRadius()) * (GetWorldRadius() + other->GetWorldRadius());
	float centerLength = (_transform->GetWorldPos() - other->GetTransform()->GetWorldPos()).Length();
	return radiusLength > centerLength;
}

float CircleCollider::GetWorldRadius()
{
	Vector2 worldScale = _transform->GetWorldScale();
	return _radius * worldScale.x * worldScale.y / 2;
}
