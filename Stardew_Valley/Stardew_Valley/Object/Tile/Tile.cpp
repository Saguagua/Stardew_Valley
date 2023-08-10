#include "framework.h"
#include "../GameObj/ObjType/BreakableItem.h"
#include "../GameObj/ObjType/PickableItem.h"
#include "TileType/ArableTile.h"
#include "TileType/FishableTile.h"
#include "../../Data/TileInfo.h"
#include "Tile.h"

Tile::Tile(string name, Vector2 pos)
:_tileName(name), _centerPos(pos)
{
}
