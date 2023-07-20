#include "framework.h"
#include "TileMap.h"
#include "../../Object/Character/Character.h"
#include "../../Object/UI/Palette.h"

TileMap::TileMap(shared_ptr<class MapInfo> mapInfo)
	:_mapName(mapInfo->GetName()), _frames(mapInfo->GetFrames()), _mapSize(mapInfo->GetSize())
{
	for (int i = 0; i < 10; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(TILE_SIZE * 1.2f);
		_colliders.push_back(col);
	}

	_tileRenderer = make_shared<TextureRect>(L"Resource/Tile/Tile.png", SaveManager::GetInstance()->GetMaxFrame(), TILE_SIZE);
	
	_frameTypes = SaveManager::GetInstance()->GetTypes();
	_maxFrame = SaveManager::GetInstance()->GetMaxFrame();

	for (int i = 0; i < _mapSize.y; i++)
	{
		for (int j = 0; j < _mapSize.x; j++)
		{
			Vector2 centerPos = Vector2(TILE_SIZE.x * j, TILE_SIZE.y * i);
			_startPoses.push_back(centerPos);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			shared_ptr<GameObject> obj = make_shared<GameObject>();
			obj->SetFrame(Vector2(j, i));
			obj->SetPos(CENTER + Vector2(i+1, j+1) * TILE_SIZE.x);
			_objs.push_back(obj);
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
			Vector2 centerPos = Vector2(TILE_SIZE.x * j, TILE_SIZE.y * i);
			_startPoses.push_back(centerPos);
			_frames.push_back(Vector2(_maxFrame.x-1, _maxFrame.y-1));
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

	for (auto obj : _objs)
	{
		obj->Update();
	}
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

void TileMap::KeyInput()
{
	Vector2 mainWorldPos = _player.lock()->GetTransform()->GetWorldPos();
	int worldIndex = GetWorldIndex(mainWorldPos);

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int index = worldIndex + j + i * _maxFrame.x;

			if (index < 0 || index >= _mapSize.x * _mapSize.y)
				continue;

			Vector2 frame = _frames[index];

			if (!(_frameTypes[frame.x + frame.y * _maxFrame.x] & Type::BLOCK))
				continue;

			_colliders[0]->SetPos(_startPoses[worldIndex + j + i * _maxFrame.x]);
			_colliders[0]->GetTransform()->Update_SRT();

			_colliders[0]->Block(_player.lock()->GetCollider());
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

		Vector2 curFrame = _frames[index];

		if (!(_frameTypes[curFrame.x + curFrame.y * _maxFrame.x] & Type::BLOCK))
			continue;

		_colliders[i]->SetPos(_startPoses[index]);
		_colliders[i]->GetTransform()->Update_SRT();
		if (_colliders[i]->Block(_player.lock()->GetCollider()))
		{
			_colliders[i]->IsCollision(_player.lock()->GetCollider());
		}
	}

	for (auto obj : _objs)
		obj->Block(_player.lock()->GetCollider());
		
}

void TileMap::ChangeTile()
{
	if (KEY_PRESS(VK_LBUTTON))
	{
		Vector2 frame = _palette.lock()->GetCurTileFrame();

		if (frame.x == -1 || frame.y == -1)
			return;

		int index = GetWorldIndex(W_MOUSE_POS);
		_frames[index] = frame;
	}
}

void TileMap::Render()
{
	if (!_isActive)
		return;
	int index = GetWorldIndex(_player.lock()->GetWorldPos());
	
	for (int i = 0; i < _frames.size(); i++)
	{
		_colliders[0]->SetPos(_startPoses[i]);
		_colliders[0]->Update();
		_colliders[0]->Render();
		_tileRenderer->SetCurFrame(_frames[i]);
		_tileRenderer->Render();
	}

	for (auto obj : _objs)
		obj->Render();
}

void TileMap::LoadMap(shared_ptr<MapInfo> info)
{
	vector<Vector2> frame = info->GetFrames();

	for (int i = 0; i < frame.size(); i++)
	{
		_frames[i] = frame[i];
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

	if (sum >= _frames.size())
		return _frames.size() - 1;
	return sum;
}