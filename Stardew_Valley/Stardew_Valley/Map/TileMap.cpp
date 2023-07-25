#include "framework.h"
#include "../Data/MapInfo.h"
#include "../Data/TileInfo.h"
#include "../Object/UI/Palette.h"
#include "../Object/Player/Player.h"
#include "TileMap.h"

TileMap* TileMap::_instance = nullptr;

TileMap::TileMap()
{
	for (int i = 0; i < 5; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(TILE_SIZE);
		_colliders.push_back(col);
	}

	_frameTypes = DATA->GetTypes();
	_tileMaxFrame = DATA->GetTileMaxFrame();
	_objectMaxFrame = DATA->GetObjectMaxFrame();
	_mapInfos = DATA->GetMapInfos();
	
	_tileRenderer = make_shared<TextureRect>(L"Resource/Tile/Tile.png", _tileMaxFrame, TILE_SIZE);
	_objectRenderer = make_shared<TextureRect>(L"Resource/Object/Objects.png", _objectMaxFrame, TILE_SIZE);

	for (int i = 0; i < MAP_SIZE.y; i++)
	{
		for (int j = 0; j < MAP_SIZE.x; j++)
		{
			Vector2 pos = Vector2(TILE_SIZE.x * j, TILE_SIZE.y * i) + TILE_SIZE * 0.5f;
			shared_ptr<TileInfo> info = make_shared<TileInfo>(pos, Vector2(_tileMaxFrame.x - 1, _tileMaxFrame.y - 1), Vector2(_objectMaxFrame.x-1, _objectMaxFrame.y-1));

			_tileInfos.push_back(info);
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

		int index = worldIndex + x + y * _mapSize.x;

		if (index < 0 || index >= _mapSize.x * _mapSize.y)
			continue;

		Vector2 curFrame = _tileInfos[index]->GetTileFrame();

		Vector2 objFrame = _tileInfos[index]->GetObjectFrame();

		if (!(_frameTypes[curFrame.x + curFrame.y * _tileMaxFrame.x] & Type::BLOCK)
			&& objFrame.x == _objectMaxFrame.x - 1 && objFrame.y == _objectMaxFrame.y - 1)
			continue;

		_colliders[i]->SetPos(_tileInfos[index]->GetCenterPos());
		_colliders[i]->GetTransform()->Update_SRT();
		_colliders[i]->Block(PLAYER->GetCollider());
	}
	
}

void TileMap::Mouse()
{
	int index = GetMouseToPlayerIndex(W_MOUSE_POS);
}

void TileMap::ChangeTile()
{
	if (KEY_PRESS(VK_LBUTTON))
	{
		int index = PALETTE->GetIndex();
		
		if (index == 0)
		{
			Vector2 frame = PALETTE->GetCurTileFrame();

			if (frame.x == -1 || frame.y == -1)
				return;

			int index = GetWorldIndex(W_MOUSE_POS);
			_tileInfos[index]->SetTileFrame(frame);
		}
		else if (index == 1)
		{
			Vector2 frame = PALETTE->GetCurObjectFrame();


			int index = GetWorldIndex(W_MOUSE_POS);
			_tileInfos[index]->SetObjectFrame(frame);
		}
	}
}

void TileMap::Render()
{
	
	for (int i = 0; i < _tileInfos.size(); i++)
	{
		_colliders[0]->SetPos(_tileInfos[i]->GetCenterPos());
		_colliders[0]->Update();
		_colliders[0]->Render();
		_tileRenderer->SetCurFrame(_tileInfos[i]->GetTileFrame());
		_tileRenderer->Render();
		_objectRenderer->SetCurFrame(_tileInfos[i]->GetObjectFrame());
		_objectRenderer->Render();
	}

}

void TileMap::ChangeMap(int index)
{
	_mapName = _mapInfos[index]->GetName();
	_mapSize = _mapInfos[index]->GetSize();
	_tileInfos = _mapInfos[index]->GetInfos();
	SetCameraRange();
}

void TileMap::SetCameraRange()
{
	float top = (_mapSize.y * TILE_SIZE.y) - WIN_HEIGHT / 2 - TILE_SIZE.y;
	float right = (_mapSize.x * TILE_SIZE.x) - WIN_WIDTH / 2 - TILE_SIZE.x;
	CAMERA->SetLeftBottom(CENTER);
	CAMERA->SetRightTop(Vector2(right, top));
}

int TileMap::GetWorldIndex(Vector2 pos)
{
	int x = pos.x / TILE_SIZE.x;
	int y = pos.y / TILE_SIZE.y;

	int sum = x + y * _mapSize.x;

	if (sum >= _tileInfos.size())
		return _tileInfos.size() - 1;

	return sum;
}

int TileMap::GetMouseToPlayerIndex(Vector2 mousePos) //µµ³¢³ª °î±ªÀÌ ¾µ ¶§ ½á¶ó
{
	Vector2 target = mousePos - PLAYER->GetWorldPos();

	int index = GetWorldIndex(mousePos);
	float angle = target.Angle() * 57.2958f;

	if (angle > -25.0f && angle <= 25.0f)
	{
		index += 1;
	}
	else if (angle > 25.0f && angle <= 70.0f)
	{
		index += 1 + _mapSize.x;
	}
	else if (angle > 70.0f && angle <= 115.0f)
	{
		index += _mapSize.x;
	}
	else if (angle > 115.0f && angle < 160.0f)
	{
		index += _mapSize.x - 1;
	}
	else if (angle > -70.0f && angle <= -25.0f)
	{
		index += 1 - _mapSize.x;
	}
	else if (angle > -115.0f && angle <= -70.0f)
	{
		index -= _mapSize.x;
	}
	else if (angle > -160.0f && angle <= -25.0f)
	{
		index -= 1 + _mapSize.x;
	}
	else
	{
		index -= 1;
	}

	return index;
}


