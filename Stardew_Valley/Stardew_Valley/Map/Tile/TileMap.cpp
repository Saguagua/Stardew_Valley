#include "framework.h"
#include "TileMap.h"
#include "../../Object/Character/Character.h"
#include "../../Object/UI/Palette.h"

TileMap::TileMap(wstring path, Vector2 size, Vector2 tileSize, shared_ptr<Character> mainCharacter)
	:_mapSize(size), _mainCharacter(mainCharacter)
{
	_transform = make_shared<Transform>();
	_tileSize = Vector2(30 , 30);
	_col = make_shared<RectCollider>(_tileSize);
	_lineRenderer = make_shared<RectLine>(_tileSize);
	_tileRenderer = ADD_TILE(path, Vector2(13, 7), _tileSize); //싱글턴 필요 없을 듯

	_frameTypes = SaveManager::GetInstance()->GetTypes();

	ReadFile(path);
}

TileMap::TileMap(Vector2 size)
	:_mapSize(size)
{
	_transform = make_shared<Transform>();
	_tileSize = Vector2(30, 30);
	_col = make_shared<RectCollider>(_tileSize);
	_lineRenderer = make_shared<RectLine>(_tileSize);
	_tileRenderer = ADD_TILE(L"Resource/Tile/Tile.png", Vector2(13, 7), _tileSize);

	_frameTypes = SaveManager::GetInstance()->GetTypes();

	CreateTileInfos();
}

void TileMap::Update()
{
	if (!_isActive)
		return;

	if (!_mainCharacter.expired())
		Play();
	if (!_palette.expired() && !_palette.lock()->GetFocus())
		CreateMap();
}

void TileMap::Play()
{
	Vector2 mainWorldPos = _mainCharacter.lock()->GetTransform()->GetWorldPos();
	int worldIndex = GetWorldIndex(mainWorldPos);

	for (int i = -1; i < 2; i++)
	{
		if (worldIndex + i * 13 < 0 || worldIndex + i * 13 > _mapSize.y - 1)
			continue;

		for (int j = -1; j < 2; j++)
		{
			if (worldIndex + j < 0 || worldIndex + j > _mapSize.x - 1)
				continue;

			Vector2 frame = _frames[worldIndex + j + i * 13];
			if (!(_frameTypes[frame.x + frame.y * 13] & Type::BLOCK))
				continue;

			_col->SetPos(_centers[worldIndex + j + i * 13]);
			_col->GetTransform()->Update_SRT();

			_col->Block(_mainCharacter.lock()->GetCollider());
		}
	}

	if (KEY_DOWN(VK_LBUTTON))
	{
		int index = GetWorldIndex(W_MOUSE_POS);
		Vector2 mouse = W_MOUSE_POS;
		Vector2 target = mouse - mainWorldPos;

		float angle = target.Angle() * 57.2958;

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

void TileMap::CreateMap()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		int index = GetWorldIndex(W_MOUSE_POS);
		Vector2 frame = _palette.lock()->GetCurTileFrame();
		if (frame.x == -1 || frame.y == -1)
			return;
		_frames[index] = frame;
	}
}

void TileMap::Render()
{
	if (_isDebug)
	{
		for (int i = 0; i < _frames.size(); i++)
		{
			_col->SetPos(_centers[i]);
			_col->Update();
			_col->GetTransform()->Set_World();
			_lineRenderer->Render();
			_tileRenderer.lock()->SetCurFrame(_frames[i]);
			_tileRenderer.lock()->Update();
			_tileRenderer.lock()->Render();
			_lineRenderer->Render();
		}
	}
	else
	{
		for (int i = 0; i < _frames.size(); i++)
		{
			_col->SetPos(_centers[i]);
			_col->Update();
			_col->GetTransform()->Set_World();
			_tileRenderer.lock()->SetCurFrame(_frames[i]);
			_tileRenderer.lock()->Update();
			_tileRenderer.lock()->Render();
		}
	}
	
}

void TileMap::LoadMap(shared_ptr<MapInfo> info)
{
	_frames = info->GetFrames();
	_mapName = info->GetName();
}

void TileMap::SetCameraRange()
{
	float Xhalf = (_mapSize.x * _tileSize.x) / 2 - _tileSize.x / 2;
	float Yhalf = (_mapSize.y * _tileSize.y) / 2 - _tileSize.y / 2;
	CAMERA->SetLeftBottom(Vector2(-Xhalf + WIN_WIDTH / 2, -Yhalf + WIN_HEIGHT / 2));
	CAMERA->SetRightTop(Vector2(Xhalf - WIN_WIDTH / 2, Yhalf - WIN_HEIGHT / 2));
}

int TileMap::GetWorldIndex(Vector2 pos)
{
	int x = pos.x / _tileSize.x;
	int y = pos.y / _tileSize.y;

	int sum = x + y * _mapSize.x;
	return sum;
}

void TileMap::CreateTileInfos()
{
	Vector2 startPos = _tileSize * 0.5f;

	for (int i = 0; i < _mapSize.y; i++)
	{
		for (int j = 0; j < _mapSize.x; j++)
		{
			Vector2 centerPos = Vector2(startPos.x + _tileSize.x * j, startPos.y + _tileSize.y * i);
			_centers.push_back(centerPos);
			_frames.push_back(Vector2(12, 6));
		}
	}
}

void TileMap::ReadFile(wstring path)
{
	//todo : 파일 읽어서 타입 저장
	Vector2 startPos = _tileSize * 0.5f;

	for (int i = 0; i < _mapSize.y; i++)
	{
		for (int j = 0; j < _mapSize.x; j++)
		{
			Vector2 centerPos = Vector2(startPos.x + _tileSize.x * j,startPos.y + _tileSize.y * i);
			_centers.push_back(centerPos);
			_frames.push_back(Vector2(12, 6));
		}
	}

}
