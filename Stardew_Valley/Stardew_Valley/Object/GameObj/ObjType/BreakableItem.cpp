#include "framework.h"
#include "PickAxe.h"
#include "BreakableItem.h"

void BreakableItem::GetDamage(shared_ptr<PickAxe> obj)
{
	if (PLAYER->AddStamina(obj->GetCost()))
	{
		_hp -= obj->GetDamage();

		if (_hp <= 0)
		{
			ObjectSpawner::GetInstance()->ActiveDropItem(_pos, _dropItemCodeMin, _countMin);
			_type = ObjectInfo::Type::BLANK;
			_objCode = 139;
			_frameIndex = 127;
		}
	}
	
}

void BreakableItem::Interaction()
{
	shared_ptr<GameObject> obj = PLAYER->GetSelectedItem();

	if (obj->GetType() == ObjectInfo::Type::PICKAXE)
	{
		GetDamage(dynamic_pointer_cast<PickAxe>(obj));
	}
}
