#include "framework.h"
#include "DeployableObject.h"

DeployableObject::DeployableObject(DeployableObject::Type type, string name, Vector2 pos)
	:GameObject(name), _type(type), _centerPos(pos)
{
}

void DeployableObject::Render(shared_ptr<Sprite> renderer, shared_ptr<RectCollider> col)
{
	col->SetPos(_centerPos);
	col->SetScale(DATA->GetXMLInfo(_name)->GetSize(_index));
	col->Update();

	col->GetTransform()->Set_World(0);

	renderer->SetImage(_name, _index);
	renderer->Render();

	col->Render();
}
