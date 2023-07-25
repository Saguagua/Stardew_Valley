#include "framework.h"
#include "TileMap.h"
#include "TileInfo.h"
#include "../../Object/Player/Player.h"
#include "../../Object/UI/Palette.h"

TileMap::TileMap(shared_ptr<class MapInfo> mapInfo)
	:_mapName(mapInfo->GetName()), _mapSize(mapInfo->GetSize())
{
	for (int i = 0; i < 10; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(TILE_SIZE * 1.2f);
		_colliders.push_back(col);
	}

	_frameTypes = DATA->GetTypes();
	_tileMaxFrame = DATA->GetTileMaxFrame();
	_objectMaxFrame = DATA->GetObjectMaxFrame();

	_tileRenderer = make_shared<TextureRect>(L"Resource/Tile/Tile.png", _tileMaxFrame, TILE_SIZE);
	_objectRenderer = make_shared<TextureRect>(L"Resource/Object/Objects.png", _objectMaxFrame, TILE_SIZE);

	_infos = mapInfo->GetInfos();
	
	for (int i = 0; i < _mapSize.y; i++)
	{
		for (int j = 0; j < _mapSize.x; j++)
		{
			Vector2 pos = Vector2(TILE_SIZE.x * j, TILE_SIZE.y * i) + TILE_SIZE * 0.5f;
			_infos[j + i * _mapSize.x]->SetStartPos(pos);
		}
	}
}

TileMap::TileMap()
	:_mapSize(MAP_SIZE)
{
	for (int i = 0; i < 5; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(TILE_SIZE);
		_colliders.push_back(col);
	}

	_frameTypes = DATA->GetTypes();
	_tileMaxFrame = DATA->GetTileMaxFrame();
	_objectMaxFrame = DATA->GetObjectMaxFrame();
	
	_tileRenderer = make_shared<TextureRect>(L"Resource/Tile/Tile.png", _tileMaxFrame, TILE_SIZE);
	_objectRenderer = make_shared<TextureRect>(L"Resource/Object/Objects.png", _objectMaxFrame, TILE_SIZE);

	for (int i = 0; i < _mapSize.y; i++)
	{
		for (int j = 0; j < _mapSize.x; j++)
		{
			Vector2 pos = Vector2(TILE_SIZE.x * j, TILE_SIZE.y * i) + TILE_SIZE * 0.5f;
			shared_ptr<TileInfo> info = make_shared<TileInfo>(pos, Vector2(_tileMaxFrame.x - 1, _tileMaxFrame.y - 1), Vector2(_objectMaxFrame.x-1, _objectMaxFrame.y-1));
		
			_infos.push_back(info);
		}
	}
}

void TileMap::Update()
{
	if (!_isActive)
		return;

	if (!_player.expired())
		Play();
	else if (!_palette.expired() && !_palette.lock()->GetFocus())
		ChangeTile();
}

void TileMap::Play()
{
	Blocking();
	Mouse();
}

void TileMap::Blocking()
{
	Vector2 mainWorldPos = _player.lock()->GetWorldPos();
	int worldIndex = GetWorldIndex(mainWorldPos);
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

		Vector2 curFrame = _infos[index]->GetTileFrame();

		Vector2 objFrame = _infos[index]->GetObjectFrame();

		if (!(_frameTypes[curFrame.x + curFrame.y * _tileMaxFrame.x] & Type::BLOCK)
			&& objFrame.x == _objectMaxFrame.x - 1 && objFrame.y == _objectMaxFrame.y - 1)
			continue;

		_colliders[i]->SetPos(_infos[index]->GetStartPos());
		_colliders[i]->GetTransform()->Update_SRT();
		_colliders[i]->Block(_player.lock()->GetCollider());
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
		int index = _palette.lock()->GetIndex();
		
		if (index == 0)
		{
			Vector2 frame = _palette.lock()->GetCurTileFrame();

			if (frame.x == -1 || frame.y == -1)
				return;

			int index = GetWorldIndex(W_MOUSE_POS);
			_infos[index]->SetTileFrame(frame);
		}
		else if (index == 1)
		{
			Vector2 frame = _palette.lock()->GetCurObjectFrame();


			int index = GetWorldIndex(W_MOUSE_POS);
			_infos[index]->SetObjectFrame(frame);
		}
	}
}

void TileMap::Render()
{
	if (!_isActive)
		return;
	
	for (int i = 0; i < _infos.size(); i++)
	{
		_colliders[0]->SetPos(_infos[i]->GetStartPos());
		_colliders[0]->Update();
		_colliders[0]->Render();
		_tileRenderer->SetCurFrame(_infos[i]->GetTileFrame());
		_tileRenderer->Render();
		_objectRenderer->SetCurFrame(_infos[i]->GetObjectFrame());
		_objectRenderer->Render();
	}

}

void TileMap::LoadMap(shared_ptr<MapInfo> info)
{
	_mapName = info->GetName();
	_mapSize = info->GetSize();
	vector<shared_ptr<TileInfo>> infos = info->GetInfos();

	for (int i = 0; i < infos.size(); i++)
	{
		_infos[i]->SetTileFrame(infos[i]->GetTileFrame());
		_infos[i]->SetObjectFrame(infos[i]->GetObjectFrame());
	}

}

void TileMap::SetCameraRange()
{
	float top = (_mapSize.y * TILE_SIZE.y) - WIN_HEIGHT / 2;
	float right = (_mapSize.x * TILE_SIZE.x) - WIN_WIDTH / 2;
	CAMERA->SetLeftBottom(Vector2(WIN_WIDTH/2, WIN_HEIGHT/2));
	CAMERA->SetRightTop(Vector2(right, top));
}

int TileMap::GetWorldIndex(Vector2 pos)
{
	int x = pos.x / TILE_SIZE.x;
	int y = pos.y / TILE_SIZE.y;

	int sum = x + y * _mapSize.x;

	if (sum >= _infos.size())
		return _infos.size() - 1;

	return sum;
}

int TileMap::GetMouseToPlayerIndex(Vector2 mousePos) //µµ³¢³ª °î±ªÀÌ ¾µ ¶§ ½á¶ó
{
	Vector2 mainWorldPos = _player.lock()->GetTransform()->GetWorldPos();
	Vector2 target = mousePos - mainWorldPos;

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

shared_ptr<MapInfo> TileMap::GetMapInfo()
{
	shared_ptr<MapInfo> info = make_shared<MapInfo>(_mapName, _mapSize, _infos);

	return info;
}
