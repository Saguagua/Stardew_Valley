#include "framework.h"
#include "DropItem.h"

DropItem::DropItem()
    :GameObject(-1)
{
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


void DropItem::Spawn(Vector2 pos, int itemCode)
{
    _isActive = true;
    _itemCode = itemCode;
    _col->SetPos(pos);
}
