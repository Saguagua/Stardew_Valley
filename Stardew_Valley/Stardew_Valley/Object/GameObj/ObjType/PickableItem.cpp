#include "framework.h"
#include "PickableItem.h"

void PickableItem::Interaction()
{
	if (DATA->AddItem(_pickCode))
	{
		_objCode = 139;
		_frameIndex = 103;
		_type = ObjectInfo::Type::BLANK;
	}
}
