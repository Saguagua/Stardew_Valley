#include "framework.h"
#include "../../BasicObj/Sprite.h"
#include "../Tile.h"
#include "../../GameObj/ObjType/DeployableObj/Crop.h"
#include "ArableTile.h"

void ArableTile::Render(shared_ptr<Sprite> renderer)
{
	Tile::Render(renderer);
	if (!_plantable)
		return;

	string name;
	if (_water)
		name = "W";
	name += "HoeDirt";

	if (_connect._down)
		name += "T";
	if (_connect._right)
		name += "L";
	if (_connect._up)
		name += "B";
	if (_connect._left)
		name += "R";

	renderer->ChangePicture(0, name);

	renderer->Render();

	/*if (!_crop.expired())
	{
		renderer->ChangePicture(_crop.lock()->GetLevel(), _crop.lock()->GetName());
		renderer->Render();
	}*/
}

void ArableTile::Plant(string cropName)
{
	_crop = ObjectSpawner::GetInstance()->CreateCrop(cropName);
}


