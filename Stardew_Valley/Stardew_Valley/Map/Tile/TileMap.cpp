#include "framework.h"
#include "TileMap.h"
#include "TileInfo.h"
#include "../../Object/Character/Character.h"
#include "../../Object/UI/Palette.h"

TileMap::TileMap(shared_ptr<class MapInfo> mapInfo)
	:_mapName(mapInfo->GetName()), _mapSize(mapInfo->GetSize())
{
	for (int i = 0; i < 10; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(TILE_SIZE * 1.2f);
		_colliders.push_back(col);
	}

	_tileRenderer = make_shared<TextureRect>(L"Resource/Tile/Tile.png", SaveManager::GetInstance()->GetMaxFrame(), TILE_SIZE);
	
	_frameTypes = SaveManager::GetInstance()->GetTypes();
	_maxFrame = SaveManager::GetInstance()->GetMaxFrame();

	vector<Vector2> frames = mapInfo->GetFrames();

	for (int i = 0; i < _mapSize.y; i++)
	{
		for (int j = 0; j < _mapSize.x; j++)
		{
			Vector2 pos = Vector2(TILE_SIZE.x * j, TILE_SIZE.y * i);
			shared_ptr<TileInfo> info = make_shared<TileInfo>(pos, frames[j + i * _mapSize.x], -1);

			_infos.push_back(info);
		}
	}
}

TileMap::TileMap()
	:_mapSize(MAP_SIZE)
{
	for (int i = 0; i < 5; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(TILE_SIZE * 1.5f);
		_colliders.push_back(col);
	}
	_tileRenderer = make_shared<TextureRect>(L"Resource/Tile/Tile.png", SaveManager::GetInstance()->GetMaxFrame(), TILE_SIZE);

	_frameTypes = SaveManager::GetInstance()->GetTypes();

	_maxFrame = SaveManager::GetInstance()->GetMaxFrame();

	for (int i = 0; i < _mapSize.y; i++)
	{
		for (int j = 0; j < _mapSize.x; j++)
		{
			Vector2 pos = Vector2(TILE_SIZE.x * j, TILE_SIZE.y * i);
			shared_ptr<TileInfo> info = make_shared<TileInfo>(pos, Vector2(_maxFrame.x - 1, _maxFrame.y - 1), -1);
		
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
	MouseInput();
}

void TileMap::MouseInput()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 mainWorldPos = _player.lock()->GetTransform()->GetWorldPos();
		Vector2 mouse = W_MOUSE_POS;
		Vector2 target = mouse - mainWorldPos;
		int index = GetWorldIndex(mouse);

		float angle = target.Angle() * 57.2958f;

		if (angle > -25.0f && angle <= 25.0f)
		{
			//_infos[worldIndex.y][worldIndex.x + 1]->curFrame.x++;
		}
		else if (angle > 25.0f && angle <= 70.0f)
		{
			//_infos[worldIndex.y + 1][worldIndex.x + 1]->curFrame.x++;
		}
		else if (angle > 70.0f && angle <= 115.0f)
		{
			//_infos[worldIndex.y + 1][worldIndex.x]->curFrame.x++;
		}
		else if (angle > 115.0f && angle < 160.0f)
		{
			//_infos[worldIndex.y + 1][worldIndex.x - 1]->curFrame.x++;
		}
		else if (angle > -70.0f && angle <= -25.0f)
		{
			//_infos[worldIndex.y - 1][worldIndex.x + 1]->curFrame.x++;
		}
		else if (angle > -115.0f && angle <= -70.0f)
		{
			//_infos[worldIndex.y - 1][worldIndex.x]->curFrame.x++;
		}
		else if (angle > -160.0f && angle <= -25.0f)
		{
			//_infos[worldIndex.y - 1][worldIndex.x - 1]->curFrame.x++;
		}
		else
		{
			//_infos[worldIndex.y][worldIndex.x - 1]->curFrame.x++;
		}
	}
	
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

		if (!(_frameTypes[curFrame.x + curFrame.y * _maxFrame.x] & Type::BLOCK))
			continue;

		_colliders[i]->SetPos(_infos[index]->GetStartPos());
		_colliders[i]->GetTransform()->Update_SRT();
		_colliders[i]->Block(_player.lock()->GetCollider());
	}
	
}

void TileMap::ChangeTile()
{
	if (KEY_PRESS(VK_LBUTTON))
	{
		Vector2 frame = _palette.lock()->GetCurTileFrame();

		if (frame.x == -1 || frame.y == -1)
			return;

		int index = GetWorldIndex(W_MOUSE_POS);
		_infos[index]->SetTileFrame(frame);
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
	}

}

void TileMap::LoadMap(shared_ptr<MapInfo> info)
{
	vector<Vector2> frame = info->GetFrames();

	for (int i = 0; i < frame.size(); i++)
	{
		_infos[i]->SetTileFrame(frame[i]);
	}

	_mapName = info->GetName();
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