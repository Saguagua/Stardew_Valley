#include "framework.h"
#include "../Tile.h"
#include "../../GameObj/ObjType/DeployableObj/Crop.h"
#include "ArableTile.h"

void ArableTile::Render(shared_ptr<Sprite> renderer, shared_ptr<RectCollider> col)
{
	col->SetPos(_centerPos);
	col->SetScale(Vector2(1,1));
	col->Update();

	col->GetTransform()->Set_World(0);

	renderer->ChangePicture(_tileName);
	renderer->Render();

	col->Render();

	if (_obj != nullptr)
	{
		_obj->Render(renderer, col);
	}
	
	if (!_plantable)
		return;

	string name;
	if (_crop != nullptr && _crop->GetWater())
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

	renderer->ChangePicture(name);
	renderer->Render();

	if (_crop != nullptr)
	{
		_crop->Render(renderer, col);
	}
}

void ArableTile::Plant(string cropName)
{
	_crop = ObjectSpawner::GetInstance()->CreateCrop(cropName);
	_crop->SetPos(_centerPos);
}

void ArableTile::Interaction()
{
	Tile::Interaction();
	if (_crop != nullptr)
	{
		_crop->Interaction();
		if (_crop->GetName() == "BLANK")
			_crop = nullptr;
	}
}


