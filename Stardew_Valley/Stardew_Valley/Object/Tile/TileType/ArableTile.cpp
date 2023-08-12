#include "framework.h"
#include "../Tile.h"
#include "../../GameObj/ObjType/DeployableObj/Crop.h"
#include "ArableTile.h"

void ArableTile::Interaction()
{
	shared_ptr<Item> obj = DATA->GetSelectedItem();

	switch (obj->GetType())
	{
	case Item::Type::HOE:
	{
		
		break;
	}
	case Item::Type::WATERINGCAN:
	{
		
		break;
	}
	case Item::Type::SEED:
	{

		break;
	}
	case Item::Type::FRTI:
	{

		break;
	}
	}
}
