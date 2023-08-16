#include "framework.h"
#include "../BasicObj/Sprite.h"
#include "GameObject.h"

void GameObject::Render(shared_ptr<Sprite> renderer)
{
	renderer->ChangePicture(0, _name);
	renderer->Render();
}
