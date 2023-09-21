#include "framework.h"
#include "DeployableObject.h"
#include "PickableItem.h"

void PickableItem::Interaction()
{
	if (PLAYERUI->GetBagActive())
		return;

	if (KEY_DOWN(VK_RBUTTON))
	{
		if (PLAYERUI->AddItem(_name))
		{
			_name = "BLANK";
			_isActive = false;
		}
	}
	
}

vector<int> PickableItem::GetProperty()
{
	return vector<int>(2, (0, 0));
}

