#include "framework.h"
#include "../Data/MapInfo.h"
#include "../Data/TileInfo.h"
#include "../Object/UI/Palette.h"
#include "../Object/Player/Player.h"
#include "../Object/Tile/Tile.h"
#include "TileMap.h"

TileMap* TileMap::_instance = nullptr;

TileMap::TileMap()
{
	for (int i = 0; i < 9; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(TILE_SIZE);
		_colliders.push_back(col);
	}
	Vector2 tileMaxFrame = DATA->GetTileMaxFrame();
	Vector2 objectMaxFrame = DATA->GetObjectMaxFrame();
	_mapInfos = DATA->GetMapInfos();
	
	_tileRenderer = make_shared<TextureRect>(L"Resource/Tile/Tile.png", tileMaxFrame, TILE_SIZE);
	_objectRenderer = make_shared<TextureRect>(L"Resource/Object/Objects.png", objectMaxFrame, TILE_SIZE);

	for (int i = 0; i < MAP_SIZE.y; i++)
	{
		for (int j = 0; j < MAP_SIZE.x; j++)
		{
			Vector2 pos = Vector2(TILE_SIZE.x * j, TILE_SIZE.y * i) + TILE_SIZE * 0.5f;
			int tileIndex = tileMaxFrame.x - 1 + (tileMaxFrame.y - 1) * tileMaxFrame.x;
			shared_ptr<Tile> tile = make_shared<Tile>(pos, tileIndex, 139);

			_tiles.push_back(tile);
		}
	}
	SetCameraRange();
}

void TileMap::Update()
{
	if (PLAYER != nullptr)
		Play();
	if (PALETTE != nullptr && !PALETTE->GetFocus())
		ChangeTile();
}

void TileMap::Play()
{
	Blocking();
	Mouse();
}

void TileMap::Blocking()
{
	int worldIndex = GetWorldIndex(PLAYER->GetWorldPos());
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

		int bitFlag = _tiles[index]->GetBitFlag();

		if (!(bitFlag & TileInfo::Type::BLOCK) && _tiles[index]->GetObj()->GetType() == ObjectInfo::Type::BLANK)
			continue;

		_colliders[i]->SetPos(_tiles[index]->GetCenterPos());
		_colliders[i]->GetTransform()->Update_SRT();
		_colliders[i]->Block(PLAYER->GetCollider());
	}
}

void TileMap::Mouse()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		shared_ptr<Tile> tile = GetMouseToPlayerIndex(W_MOUSE_POS);

		tile->Interaction();
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
			_tiles[index]->SetTileCode(code);
		}
		else if (chartIndex == 1)
		{
			int code = PALETTE->GetCurObjectCode();

			int index = GetWorldIndex(W_MOUSE_POS);
			_tiles[index]->SetObject(code);
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
		_tileRenderer->SetCurFrame(_tiles[i]->GetTileCode());
		_tileRenderer->Render();
		_objectRenderer->SetCurFrame(_tiles[i]->GetObjectFrameIndex());
		_objectRenderer->Render();
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

shared_ptr<Tile> TileMap::GetMouseToPlayerIndex(Vector2 mousePos) //µµ³¢³ª °î±ªÀÌ ¾µ ¶§ ½á¶ó
{
	Vector2 target = mousePos - PLAYER->GetWorldPos();
	int worldIndex = GetWorldIndex(PLAYER->GetWorldPos());
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


