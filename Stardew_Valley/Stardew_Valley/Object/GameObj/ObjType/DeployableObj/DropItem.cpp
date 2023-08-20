#include "framework.h"
#include "DeployableObject.h"
#include "DropItem.h"

DropItem::DropItem()
{
    _collider = make_shared<CircleCollider>(20);
    _collider->SetDebug(true);
}

void DropItem::Update()
{
    _collider ->Update();
}

void DropItem::Render(shared_ptr<Sprite> renderer)
{
    _collider->GetTransform()->Set_World(0);
    renderer->ChangePicture(_name, 0);
    renderer->Render();
    _collider->Render();
}


void DropItem::Interaction()
{
   // DATA->AddItem(_objCode);
    _isActive = false;
}

void DropItem::Spawn(string name, string itemName, Vector2 pos)
{
    _isActive = true;
    _name = name;
    _itemName = itemName;
    _collider->SetPos(pos);
}
