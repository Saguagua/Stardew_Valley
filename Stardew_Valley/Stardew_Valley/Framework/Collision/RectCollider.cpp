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

bool RectCollider::IsCollision(shared_ptr<class RectCollider> other)
{
	
	return false;
}

bool RectCollider::IsCollision(shared_ptr<class CircleCollider> other)
{
	return false;
}

RectCollider::AABB_Info RectCollider::GetAABB_Info()
{
	AABB_Info info = {};

	Vector2 worldPos = _transform->GetWorldPos();

	info.leftUp.x = worldPos.x - _size.x;
	info.leftUp.y = worldPos.y + _size.y;

	info.leftDown.x = worldPos.x - _size.x;
	info.leftDown.y = worldPos.y - _size.y;

	info.rightUp.x = worldPos.x + _size.x;
	info.rightUp.y = worldPos.y + _size.y;

	info.rightDown.x = worldPos.x + _size.x;
	info.rightDown.y = worldPos.y - _size.y;


	return info;
}
