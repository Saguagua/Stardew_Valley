#include "framework.h"
#include "Tile.h"

Tile::Tile(Vector2 pos, int tileCode, int objCode)
	:_centerPos(pos), _tileCode(tileCode)
{
	_obj = ObjectSpawner::CreateObj(objCode);
}
