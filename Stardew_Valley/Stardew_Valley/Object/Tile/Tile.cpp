#include "framework.h"
#include "TileType/ArableTile.h"
#include "TileType/FishableTile.h"
#include "Tile.h"

Tile::Tile(string name, Vector2 pos)
:_tileName(name), _centerPos(pos)
{
}

void Tile::Render(shared_ptr<Sprite> renderer, shared_ptr<RectCollider> col)
{
	col->SetPos(_centerPos);
	col->SetScale(Vector2(1, 1));
	col->Update();
	col->GetTransform()->Set_World(0);
	col->SetScale(Vector2(1,1));

	renderer->SetImage(_tileName);
	renderer->Render();

	col->Render(); // 여기 수정 필요
}

bool Tile::IsBlock()
{
	bool isBlock = DATA->GetTileInfo(_tileName) & TileType::BLOCK;
	bool objBlock = (_obj != nullptr && _obj->IsActive() && _obj->GetType() != DeployableObject::Type::CROP);

	return isBlock || objBlock;
}

void Tile::Interaction()
{
	if (_obj != nullptr)
		_obj->Interaction();
}
