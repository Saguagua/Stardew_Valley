#include "framework.h"
#include "../GameObj/ObjType/BreakableItem.h"
#include "../GameObj/ObjType/PickableItem.h"
#include "TileType/ArableTile.h"
#include "TileType/FishableTile.h"
#include "../../Data/TileInfo.h"
#include "Tile.h"

Tile::Tile(Vector2 pos, int tileCode, int objCode)
	:_centerPos(pos), _tileCode(tileCode)
{
	_obj = ObjectSpawner::CreateObj(objCode);
	if (_obj->GetType() == ObjectInfo::Type::BREAKABLE)
		dynamic_pointer_cast<BreakableItem>(_obj)->SetPos(pos);
	
	//_bitFlag = DATA->GetTileInfo(tileCode)->GetBitFlag();
}

Tile::Tile(Vector2 pos, int tileCode, int bitFlag, int objCode)
	:_centerPos(pos), _bitFlag(bitFlag), _tileCode(tileCode)
{
	_obj = ObjectSpawner::CreateObj(objCode);

	if (_obj->GetType() == ObjectInfo::Type::BREAKABLE)
		dynamic_pointer_cast<BreakableItem>(_obj)->SetPos(pos);
}

void Tile::Interaction()
{
	switch (_obj->GetType())
	{
	case ObjectInfo::Type::BREAKABLE:
	{
		dynamic_pointer_cast<BreakableItem>(_obj)->Interaction();
		break;
	}
	case ObjectInfo::Type::PICKABLE:
	{
		dynamic_pointer_cast<PickableItem>(_obj)->Interaction();
		break;
	}
	default:
	{
	}
	}
}
