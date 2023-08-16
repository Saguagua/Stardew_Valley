#include "framework.h"
#include "../../BasicObj/Sprite.h"
#include "../Tile.h"
#include "../../GameObj/ObjType/DeployableObj/Crop.h"
#include "ArableTile.h"

void ArableTile::Render(shared_ptr<Sprite> renderer)
{
	Tile::Render(renderer);
	if (_hoeDirtName == "BLANK")
		return;
	renderer->ChangePicture(0, _hoeDirtName);
	renderer->Render();
}