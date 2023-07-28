#include "framework.h"
#include "GameObject.h"

bool GameObject::AddCount()
{
    if (_maxCount == _count)
        return false;

    _count++;

    return true;
}
