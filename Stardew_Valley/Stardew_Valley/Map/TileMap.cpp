#include "framework.h"
#include "../Object/Tile/TileType/ArableTile.h"
#include "TileMap.h"

TileMap::TileMap()
{
	_collider = make_shared<RectCollider>(TILE_SIZE);

	_renderer = make_shared<Sprite>(XMLPATH, "BLANK", TILE_SIZE, SpriteType::OBJECT);
	_focusRenderer = make_shared<SingleColorRect>(TILE_SIZE * 0.9f);
	_focusRenderer->SetColor(XMFLOAT4(0, 1, 0, 0.5));

	_mapInfos = DATA->GetMapInfos();
	ChangeMap(0);
}

void TileMap::Update()
{

}


void TileMap::Blocking(shared_ptr<RectCollider> col)
{
	int worldIndex = GetWorldIndex(col->GetWorldPos());

	int proximateTileIndex = -1;
	float proximateTileDistance = 100000.0f;

	for (int i = -1; i < 2; i++)
	{
		{
			for (int j = -1; j < 2; j++)
			{
				int index = worldIndex + i + j * _curMapSize.x;

				if (index < 0 || index >= _curMapSize.x * _curMapSize.y)
					continue;

				if (!_tiles[index]->IsBlock())
					continue;

				float length = (_tiles[index]->GetCenterPos() - col->GetWorldPos()).Length();

				if (length < proximateTileDistance)
				{
					proximateTileIndex = index;
					proximateTileDistance = length;
				}

			}
		}
	}

	if (proximateTileIndex != -1)
	{
		_collider->SetPos(_tiles[proximateTileIndex]->GetCenterPos());
		_collider->Update();
		_collider->Block(col);
	}
}

void TileMap::ChangeTile()
{
	if (KEY_PRESS(VK_LBUTTON))
	{
		int chartIndex = PALETTE->GetIndex();
		
		if (chartIndex == 0)
		{
			int code = PALETTE->GetCurTileCode();

			if (code == -1)
				return;

			int index = GetWorldIndex(W_MOUSE_POS);
			//_tiles[index]->SetTileCode(code);
		}
		else if (chartIndex == 1)
		{
			int code = PALETTE->GetCurObjectCode();

			int index = GetWorldIndex(W_MOUSE_POS);
			//_tiles[index]->SetObject(code);
		}
	}
}

void TileMap::SetHoeDirt(int index) //algorithm
{
	auto thisTile = dynamic_pointer_cast<ArableTile>(_tiles[index]);
	int maxIndex = _curMapSize.x * _curMapSize.y;

	if (index + 1 < maxIndex)
	{
		auto tile = dynamic_pointer_cast<ArableTile>(_tiles[index + 1]);
		
		if (tile != nullptr && tile->GetPlantable())
		{
			tile->GetConnect()._right = true;
			thisTile->GetConnect()._left = true;
		}
		else
		{
			thisTile->GetConnect()._left = false;
		}
	}

	if (index + _curMapSize.x < maxIndex)
	{
		auto connectedTile = dynamic_pointer_cast<ArableTile>(_tiles[index + _curMapSize.x]);

		if (connectedTile != nullptr && connectedTile->GetPlantable())
		{
			connectedTile->GetConnect()._up = true;
			thisTile->GetConnect()._down = true;
		}
		else
		{
			thisTile->GetConnect()._down = false;
		}
	}

	if (index - 1 > -1)
	{
		auto tile = dynamic_pointer_cast<ArableTile>(_tiles[index - 1]);

		if (tile != nullptr && tile->GetPlantable())
		{
			tile->GetConnect()._left = true;
			thisTile->GetConnect()._right = true;
		}
		else
		{
			thisTile->GetConnect()._right = false;
		}
	}

	if (index - _curMapSize.x > -1)
	{
		auto tile = dynamic_pointer_cast<ArableTile>(_tiles[index - _curMapSize.x]);

		if (tile != nullptr && tile->GetPlantable())
		{
			tile->GetConnect()._down = true;
			thisTile->GetConnect()._up = true;
		}
		else
		{
			thisTile->GetConnect()._up = false;
		}
	}
}

void TileMap::Hoeing(Vector2 originPos, Vector2 targetPos, short level)
{
	auto indices = GetFocusedIndices(originPos, targetPos, level);

	for (auto index : indices)
	{
		auto tile = dynamic_pointer_cast<ArableTile>(_tiles[index]);

		if (tile != nullptr)
			tile->SetPlantable(true);

		_tiles[index]->SetFocus(false);

		SetHoeDirt(index);
	}
}

void TileMap::Watering(Vector2 originPos, Vector2 targetPos, short level)
{
	auto indices = GetFocusedIndices(originPos, targetPos, level);

	for (auto index : indices)
	{
		auto aTile = dynamic_pointer_cast<ArableTile>(_tiles[index]);

		if (aTile != nullptr)
		{
			if (aTile->GetCrop() != nullptr)
				aTile->GetCrop()->SetWater(true);
		}

		_tiles[index]->SetFocus(false);
	}
}

void TileMap::Charging(Vector2 originPos, Vector2 targetPos, short level)
{
	auto indices = GetFocusedIndices(originPos, targetPos, level);

	for (auto index : indices)
	{
		_tiles[index]->SetFocus(true);
	}
}

void TileMap::Render()
{
	for (int i = 0; i < _tiles.size(); i++)
	{
		_collider->SetPos(_tiles[i]->GetCenterPos());
		_collider->Update();
		_collider->Render();
		_tiles[i]->Render(_renderer, _collider);

		if (_tiles[i]->IsFocus())
			_focusRenderer->Render();
	}
}

void TileMap::ChangeMap(int index)
{
	_curMapName = _mapInfos[index]->GetName();
	_curMapSize = _mapInfos[index]->GetSize();
	_tiles = _mapInfos[index]->GetInfos();
	SetCameraRange();
}

void TileMap::SetCameraRange()
{
	float top = (_curMapSize.y * TILE_SIZE.y) - WIN_HEIGHT / 2 - TILE_SIZE.y;
	float right = (_curMapSize.x * TILE_SIZE.x) - WIN_WIDTH / 2 - TILE_SIZE.x;
	CAMERA->SetLeftBottom(CENTER);
	CAMERA->SetRightTop(Vector2(right, top));
}

int TileMap::GetWorldIndex(Vector2 pos)
{
	int x = pos.x / TILE_SIZE.x;
	int y = pos.y / TILE_SIZE.y;

	int sum = x + y * _curMapSize.x;

	if (sum >= _tiles.size())
		return _tiles.size() - 1;

	return sum;
}

int TileMap::GetFocusedIndex(Vector2 orginPos, Vector2 targetPos)
{
	Vector2 target = targetPos - orginPos;
	int worldIndex = GetWorldIndex(orginPos);
	float angle = target.Angle() * 57.2958f;

	if (angle > -25.0f && angle <= 25.0f)
	{
		worldIndex += 1;
	}
	else if (angle > 25.0f && angle <= 70.0f)
	{
		worldIndex += 1 + _curMapSize.x;
	}
	else if (angle > 70.0f && angle <= 115.0f)
	{
		worldIndex += _curMapSize.x;
	}
	else if (angle > 115.0f && angle < 160.0f)
	{
		worldIndex += _curMapSize.x - 1;
	}
	else if (angle > -70.0f && angle <= -25.0f)
	{
		worldIndex += 1 - _curMapSize.x;
	}
	else if (angle > -115.0f && angle <= -70.0f)
	{
		worldIndex -= _curMapSize.x;
	}
	else if (angle > -160.0f && angle <= -25.0f)
	{
		worldIndex -= 1 + _curMapSize.x;
	}
	else
	{
		worldIndex -= 1;
	}
	if (worldIndex < 0)
		worldIndex = 0;
	else if (worldIndex > _curMapSize.x * _curMapSize.y)
		worldIndex = _curMapSize.x * _curMapSize.y - 1;

	return worldIndex;
}

shared_ptr<Tile> TileMap::GetFocusedTile(Vector2 orginPos, Vector2 targetPos)
{
	return _tiles[GetFocusedIndex(orginPos, targetPos)];
}

vector<shared_ptr<Tile>> TileMap::GetFocusedTiles(Vector2 point, short level)
{
	/*Vector2 target = point - Player::GetInstance()->GetWorldPos();
	int worldIndex = GetWorldIndex(Player::GetInstance()->GetWorldPos());
	float angle = target.Angle() * 57.2958f;
	int dir, dir2;

	if (angle > -35.0f && angle <= 35.0f)
	{
		dir = 1;
		dir2 = _curMapSize.x;
	}
	else if (angle > 35.0f && angle <= 105.0f)
	{
		dir = _curMapSize.x;
		dir2 = 1;
	}
	else if (angle > -105.0f && angle <= -35.0f)
	{
		dir = -_curMapSize.x;
		dir2 = -1;
	}
	else
	{
		dir = -1;
		dir2 = -_curMapSize.x;
	}

	worldIndex += dir;

	vector<shared_ptr<Tile>> tiles;

	switch (level)
	{
	case 0:
	{
		tiles.push_back(_tiles[worldIndex]);
		break;
	}
	case 1:
	{
		for (int i = 0; i < 3; i++)
		{
			if (worldIndex + i * dir >= 0 && worldIndex + i * dir < _curMapSize.x * _curMapSize.y)
				tiles.push_back(_tiles[worldIndex + i * dir]);
		}
		break;
	}
	case 2:
	{

		for (int i = -2; i < 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (worldIndex + j * dir + (dir2 + i * dir2) >= 0 && worldIndex + j * dir + (dir2 + i * dir2) < _curMapSize.x * _curMapSize.y)
					tiles.push_back(_tiles[worldIndex + j * dir + (dir2 + i * dir2)]);
			}
		}
		break;
	}
	}

	return tiles;*/
	vector<shared_ptr<Tile>> tiles;
	return tiles;
}

vector<int> TileMap::GetFocusedIndices(Vector2 originPos, Vector2 targetPos, short level)
{
	Vector2 target = targetPos - originPos;
	int worldIndex = GetWorldIndex(originPos);
	int dir, dir2;

	if (abs(target.x) > abs(target.y))
	{
		if (target.x < 0)
			dir = -1;
		else
			dir = 1;
		dir2 = _curMapSize.x;
	}
	else
	{
		if (target.y < 0)
			dir = -_curMapSize.x;
		else
			dir = _curMapSize.x;
		dir2 = 1;
	}

	worldIndex += dir;

	vector<int> indices;

	switch (level)
	{
	case 0:
	{
		indices.push_back(worldIndex);
		break;
	}
	case 1:
	{
		for (int i = 0; i < 3; i++)
		{
			if (worldIndex + i * dir >= 0 &&
				worldIndex + i * dir < _curMapSize.x * _curMapSize.y)
				indices.push_back(worldIndex + i * dir);
		}
		break;
	}
	case 2:
	{

		for (int i = -2; i < 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (worldIndex + j * dir + (dir2 + i * dir2) >= 0 &&
					worldIndex + j * dir + (dir2 + i * dir2) < _curMapSize.x * _curMapSize.y)
					indices.push_back(worldIndex + j * dir + (dir2 + i * dir2));
			}
		}
		break;
	}
	}

	return indices;
}


