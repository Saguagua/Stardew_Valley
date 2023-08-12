#include "framework.h"
#include "DeployableObject.h"
#include "SpawnInfo.h"
#include "DropItem.h"

DropItem::DropItem()
{
    _collider = make_shared<CircleCollider>(20);
    _dragArea = make_shared<CircleCollider>(100);
    _dragArea->SetDebug(true);
    _dragArea->SetParent(_collider->GetTransform());
}

void DropItem::Update()
{
    _collider ->Update();
    _dragArea->Update();
}

void DropItem::Render()
{
    _collider->Render();
    _dragArea->Render();
}


void DropItem::Interaction()
{
   // DATA->AddItem(_objCode);
    _isActive = false;
}

void DropItem::Spawn(string name, shared_ptr<SpawnInfo> data)
{
    _isActive = true;
    _itemName = name;
    //_collider->SetPos(pos);
}
