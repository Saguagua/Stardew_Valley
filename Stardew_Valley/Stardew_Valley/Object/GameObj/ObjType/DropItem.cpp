#include "framework.h"
#include "DropItem.h"

DropItem::DropItem()
    :GameObject(125, 125, 1, 1)
{
    _type = ObjectInfo::Type::DROP;
    _col = make_shared<CircleCollider>(20);
}

void DropItem::Update()
{
    _col->Update();
}

void DropItem::Render()
{
    _col->Render();
}


void DropItem::Spawn(Vector2 pos, int objCode, int frameIndex, int itemCode)
{
    _isActive = true;
    _objCode = objCode;
    _frameIndex = frameIndex;
    _itemCode = itemCode;
    _col->SetPos(pos);
}
