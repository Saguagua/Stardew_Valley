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
