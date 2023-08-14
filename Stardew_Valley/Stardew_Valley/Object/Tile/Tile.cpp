#include "framework.h"
#include "TileType/ArableTile.h"
#include "TileType/FishableTile.h"
#include "../GameObj/ObjType/DeployableObj/DeployableObject.h"
#include "../../Data/TileInfo.h"
#include "Tile.h"

Tile::Tile(string name, Vector2 pos, string objName)
:_tileName(name), _centerPos(pos)
{
}

void Tile::Interaction()
{
	_obj->Interaction();
}
