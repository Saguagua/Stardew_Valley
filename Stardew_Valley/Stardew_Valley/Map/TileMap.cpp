#include "framework.h"
#include "../Data/MapInfo.h"
#include "../Data/TileInfo.h"
#include "../Object/UI/Palette.h"
#include "../Object/Player/Player.h"
#include "../Object/Tile/Tile.h"
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

	_mapInfos = DATA->GetMapInfos();
	
	_tileRenderer = make_shared<Sprite>(L"Resource/Tile/Tiles.png", "Dirt", TILE_SIZE);
	_objectRenderer = make_shared<Sprite>(L"Resource/Object/Objects.png", "Potato", TILE_SIZE);

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
	int worldIndex = GetWorldIndex(_playerInfo.lock()->GetWorldPos());
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

		bool isBlock = _tileInfos[_tiles[index]->GetName()]->GetBitFlag() & TileInfo::Type::BLOCK;
		bool objBlock = (_tiles[index]->GetObj() != nullptr &&
			_tiles[index]->GetObj()->GetType() != DeployableObject::Type::CROP);
		
		if (!isBlock && !objBlock)
			continue;

		_colliders[i]->SetPos(_tiles[index]->GetCenterPos());
		_colliders[i]->GetTransform()->Update_SRT();
		_colliders[i]->Block(_playerInfo.lock()->GetCollider());
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

void TileMap::UpdateInfo()
{
}

void TileMap::Dead()
{
}

void TileMap::Render()
{
	for (int i = 0; i < _tiles.size(); i++)
	{
		_colliders[0]->SetPos(_tiles[i]->GetCenterPos());
		_colliders[0]->Update();
		_colliders[0]->Render();
		_tileRenderer->ChangePicture(0, _tiles[i]->GetName());
		_tileRenderer->Render();
		if (_tiles[i]->GetObj() != nullptr)
		{
			_objectRenderer->ChangePicture(0, _tiles[i]->GetObjName());
			_objectRenderer->Render();
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

shared_ptr<Tile> TileMap::GetMouseToPlayerIndex() //µµ³¢³ª °î±ªÀÌ ¾µ ¶§ ½á¶ó
{
	Vector2 target = W_MOUSE_POS - _playerInfo.lock()->GetWorldPos();
	int worldIndex = GetWorldIndex(_playerInfo.lock()->GetWorldPos());
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

	return _tiles[worldIndex];
}


