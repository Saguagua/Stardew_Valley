#include "framework.h"
#include "../Tile.h"
#include "ArableTile.h"

void ArableTile::Interaction()
{
	Tile::Interaction();
	shared_ptr<GameObject> obj = DATA->GetSelectedItem();

	switch (obj->GetType())
	{
	case ObjectInfo::Type::HOE:
	{
		break;
	}
	case ObjectInfo::Type::WATERINGCAN:
	{
		break;
	}
	case ObjectInfo::Type::SEED:
	{
		break;
	}
	case ObjectInfo::Type::FARMMING:
	{
		break;
	}
	}
}
