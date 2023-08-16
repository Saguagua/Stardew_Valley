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
		if (_obj == nullptr && _crop.expired())
			_plantable = true;
		break;
	}
	case Item::Type::WATERINGCAN:
	{
		if (!_crop.expired())
			_crop.lock()->Watering();
		break;
	}
	case Item::Type::SEED:
	{
		if (!_crop.expired())
			_crop = ObjectSpawner::GetInstance()->CreateCrop(obj->GetName(), 0, 2);
		break;
	}
	case Item::Type::FRTI:
	{
		
		break;
	}
	}
}
