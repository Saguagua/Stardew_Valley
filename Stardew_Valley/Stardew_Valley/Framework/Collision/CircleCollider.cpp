#include "framework.h"
#include "RectCollider.h"
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

	if (_isDebug)
		_renderer->Render();
}

bool CircleCollider::IsCollision(Vector2 other)
{
	float worldRadius = GetWorldRadius();
	Vector2 pos = GetWorldPos();
	float length = (other - pos).Length();

	return length < worldRadius;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other)
{
	return other->IsCollision(shared_from_this());
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	float len1 = GetWorldRadius();
	float len2 = other->GetWorldRadius();
	//float radiusLength = (len1 + len2) * (len1 + len2);
	float radiusLength = (len1 + len2);

	Vector2 pos1 = _transform->GetWorldPos();
	Vector2 pos2 = other->GetTransform()->GetWorldPos();
	float centerLength = (pos1 - pos2).Length();

	return radiusLength > centerLength;
}

bool CircleCollider::Block(shared_ptr<CircleCollider> other)
{
	float len1 = GetWorldRadius();
	float len2 = other->GetWorldRadius();
	//float radiusLength = (len1 + len2) * (len1 + len2);
	float radiusLength = (len1 + len2);

	Vector2 pos1 = _transform->GetWorldPos();
	Vector2 pos2 = other->GetTransform()->GetWorldPos();
	float centerLength = (pos2 - pos1).Length();

	if (centerLength >= radiusLength)
		return false;

	float powerf = radiusLength - centerLength;
	powerf = sqrt(powerf);
	Vector2 power = (pos2 - pos1).Normalize();
	
			
	other->AddPos(power * DELTA_TIME * 200);

	return true;
}

float CircleCollider::GetWorldRadius()
{
	Vector2 worldScale = _transform->GetWorldScale();
	worldScale.x = abs(worldScale.x);
	return _radius * (worldScale.x + worldScale.y) / 2;
}