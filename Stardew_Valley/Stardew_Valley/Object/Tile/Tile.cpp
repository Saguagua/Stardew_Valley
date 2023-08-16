#include "framework.h"
#include "../BasicObj/Sprite.h"
#include "TileType/ArableTile.h"
#include "TileType/FishableTile.h"
#include "../GameObj/ObjType/DeployableObj/DeployableObject.h"
#include "../../Data/TileInfo.h"
#include "Tile.h"

Tile::Tile(string name, Vector2 pos)
:_tileName(name), _centerPos(pos)
{
}

void Tile::Render(shared_ptr<class Sprite> renderer)
{
	renderer->ChangePicture(0,_tileName);
	renderer->Render();
}
