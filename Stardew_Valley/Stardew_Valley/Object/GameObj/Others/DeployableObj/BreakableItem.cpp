#include "framework.h"
#include "DeployableObject.h"
#include "BreakableItem.h"

void BreakableItem::Interaction()
{
	auto item = PLAYER->GetSelectedItem();

	if (item->GetType() == _breakType)
	{
		_hp -= item->GetVals()[2];

		if (_hp <= 0)
		{
			vector<DropInfo::Data> dropDatas = DATA->GetDropInfo(_name)->GetDatas();

			for (int i = 0; i < dropDatas.size(); i++)
			{
				int random = rand() % 100 + 1;
				if (dropDatas[i]._percent >= random)
				{
					OBSPAWNER->ActiveDropItem(dropDatas[i]._name, dropDatas[i]._name, _centerPos, 1);
				}
			}

			_name = "BLANK";
			_isActive = false;
		}
	}
}