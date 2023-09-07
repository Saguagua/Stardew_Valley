#include "framework.h"
#include "../Tile.h"
#include "ArableTile.h"

void ArableTile::Render(shared_ptr<Sprite> renderer, shared_ptr<RectCollider> col)
{
	col->SetPos(_centerPos);
	col->SetScale(Vector2(1,1));
	col->Update();

	col->GetTransform()->Set_World(0);

	renderer->SetImage(_tileName);
	renderer->Render();

	col->Render();
	
	if (!_plantable)
		return;

	string name;

	auto crop = dynamic_pointer_cast<Crop>(_obj);

	if (crop != nullptr && crop->GetWater())
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

	renderer->SetImage(name);
	renderer->Render();
}

void ArableTile::Plant(string cropName)
{
	_obj = ObjectSpawner::GetInstance()->CreateObj(cropName);
	_obj->SetPos(_centerPos);
}

void ArableTile::Interaction()
{
	Tile::Interaction();

	if (_obj != nullptr)
	{
		_obj->Interaction();
	}
}


