#include "framework.h"
#include "GameObject.h"

GameObject::GameObject(int itemCode)
	:_itemCode(itemCode)
{
}

void GameObject::Update()
{
	if (!_isActive)
		return;
}

void GameObject::Render()
{
	if (!_isActive)
		return;
}

void GameObject::SetPos(Vector2 pos)
{
}

void GameObject::SetFrame(Vector2 frame)
{
}

void GameObject::Spawn(int itemCode, Vector2 pos)
{

}