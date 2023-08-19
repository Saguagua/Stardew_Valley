#include "framework.h"
#include "DeployableObject.h"

DeployableObject::DeployableObject(DeployableObject::Type type, string name, Vector2 size)
	:GameObject(name), _type(type)
{
	Vector2 objSize(size.x * TILE_SIZE.x, size.y * TILE_SIZE.y);
	_collider = make_shared<RectCollider>(objSize);
}
