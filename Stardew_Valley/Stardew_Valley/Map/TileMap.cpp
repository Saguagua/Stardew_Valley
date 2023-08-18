#include "framework.h"
#include "../Object/UI/Palette.h"
#include "../Object/Player/Player.h"
#include "../Object/Tile/TileType/ArableTile.h"
#include "../Object/BasicObj/Sprite.h"
#include "TileMap.h"

TileMap* TileMap::_instance = nullptr;

TileMap::TileMap()
{
	for (int i = 0; i < 9; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(TILE_SIZE);
		_colliders.push_back(col);
	}
	
	_tileRenderer = make_shared<Sprite>(L"Resource/Tile/Tiles.png", "Dirt", TILE_SIZE);
	_objectRenderer = make_shared<Sprite>(L"Resource/Object/Objects.png", "Potato", TILE_SIZE);
	_focusRenderer = make_shared<SingleColorRect>(TILE_SIZE * 0.9f);
	_focusRenderer->SetColor(XMFLOAT4(0, 1, 0, 0.5));

	_mapInfos = DATA->GetMapInfos();
	ChangeMap(0);
}

void TileMap::Update()
{
	if (PALETTE != nullptr && !PALETTE->GetFocus())
		ChangeTile();
	else
		Play();
}

void TileMap::Play()
{
	Blocking();
}

void TileMap::Blocking()
{
	int worldIndex = GetWorldIndex(Player::GetInstance()->GetWorldPos());
	int x = -2;
	int y = -1;

	for (int i = 1; i < _colliders.size(); i++)
	{
		x += 1;

		if (x == 2)
		{
			x = -1;
			y += 1;
		}

		int index = worldIndex + x + y * _curMapSize.x;

		if (index < 0 || index >= _curMapSize.x * _curMapSize.y)
			continue;

		bool isBlock = _tileInfos[_tiles[index]->GetName()] & TileType::BLOCK;

		bool objBlock = (_tiles[index]->GetObj() != nullptr &&
			_tiles[index]->GetObj()->GetType() != DeployableObject::Type::CROP);
		
		if (!isBlock && !objBlock)
			continue;

		_colliders[i]->SetPos(_tiles[index]->GetCenterPos());
		_colliders[i]->GetTransform()->Update_SRT();
		_colliders[i]->Block(Player::GetInstance()->GetCollider());
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

void TileMap::UpdateInfo()
{
}

void TileMap::Dead()
{
}

void TileMap::Hoeing(Vector2 point, short level)
{
	if (KEY_UP(VK_LBUTTON))
	{
		auto indices = GetFocusedIndices(point, level);

		for (auto index : indices)
		{
			auto tile = dynamic_pointer_cast<ArableTile>(_tiles[index]);

			if (tile != nullptr)
				tile->SetPlantable(true);

			_tiles[index]->SetFocus(false);

			SetHoeDirt(index);
		}
	}
	else
	{
		auto indices = GetFocusedIndices(point, level);

		for (auto index : indices)
		{
			_tiles[index]->SetFocus(true);
		}
	}
}

void TileMap::Watering(Vector2 point, short level)
{
	auto indices = GetFocusedIndices(point, level);

	for (auto index : indices)
	{
		auto aTile = dynamic_pointer_cast<ArableTile>(_tiles[index]);

		if (aTile != nullptr)
		{
			aTile->SetWater(true);
		}
	}
}

void TileMap::Render()
{
	for (int i = 0; i < _tiles.size(); i++)
	{
		_colliders[0]->SetPos(_tiles[i]->GetCenterPos());
		_colliders[0]->Update();
		_colliders[0]->Render();
		_tiles[i]->Render(_tileRenderer);
		if (_tiles[i]->IsFocus())
			_focusRenderer->Render();
		if (_tiles[i]->GetObj() != nullptr)
		{
			_tiles[i]->GetObj()->Render(_objectRenderer);
		}
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

int TileMap::GetFocusedIndex()
{
	Vector2 target = W_MOUSE_POS - Player::GetInstance()->GetWorldPos();
	int worldIndex = GetWorldIndex(Player::GetInstance()->GetWorldPos());
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

shared_ptr<Tile> TileMap::GetFocusedBlock()
{
	return _tiles[GetFocusedIndex()];
}

vector<shared_ptr<Tile>> TileMap::GetFocusedBlocks(Vector2 point, short level)
{
	Vector2 target = point - Player::GetInstance()->GetWorldPos();
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

	return tiles;
}

vector<int> TileMap::GetFocusedIndices(Vector2 point, short level)
{
	Vector2 target = point - Player::GetInstance()->GetWorldPos();
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
			if (worldIndex + i * dir >= 0 && worldIndex + i * dir < _curMapSize.x * _curMapSize.y)
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
				if (worldIndex + j * dir + (dir2 + i * dir2) >= 0 && worldIndex + j * dir + (dir2 + i * dir2) < _curMapSize.x * _curMapSize.y)
					indices.push_back(worldIndex + j * dir + (dir2 + i * dir2));
			}
		}
		break;
	}
	}

	return indices;
}


