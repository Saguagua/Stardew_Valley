#include "framework.h"
#include "../Object/Tile/TileType/ArableTile.h"
#include "TileMap.h"

TileMap::TileMap(vector<shared_ptr<MapInfo>>& mapInfo)
	:_mapInfos(mapInfo)
{
	_collider = make_shared<RectCollider>(TILE_SIZE);

	_renderer = make_shared<Sprite>("BLANK", TILE_SIZE, SpriteType::OBJECT);
	_focusRenderer = make_shared<SingleColorRect>(TILE_SIZE * 0.9f);
	_focusRenderer->SetColor(XMFLOAT4(0, 1, 0, 0.5));

	ChangeMap(0);

	for (int i = 0; i < _mapInfos.size(); i++)
	{
		vector<shared_ptr<Tile>> tiles = _mapInfos[i]->GetInfos();

		for (int j = 0; j < tiles.size(); j++)
		{
			auto tile = dynamic_pointer_cast<ArableTile>(tiles[j]);
			if (tile == nullptr)
				continue;

			if (tile->GetPlantable())
			{
				SetHoeDirt(j);
			}
		}
	}
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

void TileMap::ChangeTile(Vector2 pos, int paletteIndex, string name)
{
	if (paletteIndex == 0)
	{
		int index = GetWorldIndex(pos);
		_tiles[index]->SetName(name);
	}
	else if (paletteIndex == 1)
	{
		int index = GetWorldIndex(pos);

		if (name == "BLANK")
		{
			OBJECT_SPAWNER->DeleteObj(_mapInfos[_curMapIndex], index);
			return;
		}
		else
		{
			auto info = DATA->GetDeployInfo(name);
			auto vals = info->GetVals();
			OBJECT_SPAWNER->CreateObj(_mapInfos[_curMapIndex], index, name, vals[0], vals[1]);
		}
	}
}

void TileMap::SetHoeDirt(int index) //algorithm
{
	auto thisTile = dynamic_pointer_cast<ArableTile>(_tiles[index]);
	if (thisTile == nullptr)
		return;

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
			auto crop = dynamic_pointer_cast<Crop>(aTile->GetObj());

			if (crop != nullptr)
			{
				crop->SetWater(true);
			}
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
		_tiles[i]->Render(_renderer, _collider);

		if (_tiles[i]->IsFocus())
			_focusRenderer->Render();
	}

	for (int i = 0; i < _tiles.size(); i++) //DepthView 사용필요
	{
		auto obj = _tiles[i]->GetObj();

		if (obj)
		{
			_collider->SetPos(_tiles[i]->GetCenterPos());
			_collider->Update();
			obj->Render(_renderer, _collider);
		}
		
	}
	
	for (int i = 0; i < _teleports.size(); i++)
	{
		_teleports[i]->_collider->Render();
	}
}

void TileMap::ChangeMap(int index)
{
	_curMapIndex = index;
	_curMapName = _mapInfos[index]->GetName();
	_curMapSize = _mapInfos[index]->GetSize();
	_tiles = _mapInfos[index]->GetInfos();
	_teleports = _mapInfos[index]->GetTeleports();
	LightManager::GetInstance()->Set_Light(_mapInfos[index]->GetLightColors(), _mapInfos[index]->GetLightPoses());
	LightManager::GetInstance()->_sunOn = _mapInfos[index]->_sunOn;
	LightManager::GetInstance()->UpdateSun();
	SetCameraRange();
}

void TileMap::SetCameraRange()
{
	float top;
	float right;
	float left;
	float bottom;

	if (_curMapSize.y * TILE_SIZE.y < WIN_HEIGHT)
	{
		top = _curMapSize.y * TILE_SIZE.y * 0.5f;
		bottom = top;
	}
	else
	{
		top = (_curMapSize.y * TILE_SIZE.y) - WIN_HEIGHT / 2;
		bottom = CENTER.y;
	}

	if (_curMapSize.x * TILE_SIZE.x < WIN_WIDTH)
	{
		right = _curMapSize.x * TILE_SIZE.x * 0.5f;
		left = right;
	}
	else
	{
		right = (_curMapSize.x * TILE_SIZE.x) - WIN_WIDTH / 2;
		left = CENTER.x;
	}

	CAMERA->SetLeftBottom(Vector2(left, bottom));
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

shared_ptr<Tile> TileMap::GetWorldTile(Vector2 pos)
{
	return _tiles[GetWorldIndex(pos)];
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


