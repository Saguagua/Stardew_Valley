#include "framework.h"
#include "DeployableObject.h"
#include "DropItem.h"

DropItem::DropItem()
    :DeployableObject(ObjectInfo::Type::DROP)
{
    _col = make_shared<CircleCollider>(20);
    _dragArea = make_shared<CircleCollider>(100);
    _dragArea->SetDebug(true);
    _dragArea->SetParent(_col->GetTransform());
}

void DropItem::Update()
{
    _col->Update();
    _dragArea->Update();
}

void DropItem::Render()
{
    _col->Render();
    _dragArea->Render();
}


void DropItem::Interaction()
{
   // DATA->AddItem(_objCode);
    _isActive = false;
}


void DropItem::Spawn(string name, vector<short> vals)
{
    _isActive = true;
    _name = name;
    //_itemName = itemName;
    //_collider->SetPos(pos);
}
