#include "framework.h"
#include "TileInfo.h"

TileInfo::TileInfo(Vector2 pos, Vector2 tileFrame, Vector2 objFrame)
	:_centerPos(pos), _tileFrame(tileFrame), _objFrame(objFrame)
{
}

void TileInfo::PlayerInteration(shared_ptr<Player> player)
{

}
