#include "framework.h"
#include "DeployableObject.h"
#include "PickableItem.h"

void PickableItem::Interaction()
{
	if (PLAYERUI->GetBagActive())
		return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		PLAYERUI->AddItem(_name);
	}
	
}

vector<int> PickableItem::GetProperty()
{
	return vector<int>(2, (0, 0));
}

