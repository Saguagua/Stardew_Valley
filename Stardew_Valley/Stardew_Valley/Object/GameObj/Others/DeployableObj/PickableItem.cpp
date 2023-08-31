#include "framework.h"
#include "DeployableObject.h"
#include "PickableItem.h"

void PickableItem::Interaction()
{
	/*if (DATA->AddItem(_pickCode))
	{
		_objCode = 139;
		_frameIndex = 103;
		_type = ObjectInfo::Type::BLANK;
	}*/
}

vector<int> PickableItem::GetProperty()
{
	return vector<int>(2, (0, 0));
}

