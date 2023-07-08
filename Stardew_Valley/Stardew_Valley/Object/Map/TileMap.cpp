#include "framework.h"
#include "TileMap.h"
#include "../Character/Character.h"
#include "../UI/Palette.h"

TileMap::TileMap(wstring path, Vector2 size, Vector2 tileSize, shared_ptr<Character> mainCharacter)
	:_mapSize(size), _mainCharacter(mainCharacter)
{
	_transform = make_shared<Transform>();
	_tileSize = Vector2(30 , 30);
	_col = make_shared<RectCollider>(_tileSize);
	_lineRenderer = make_shared<RectLine>(_tileSize);
	_tileRenderer = ADD_TILE(path, _mapSize, _tileSize);
	ReadFile(path);
}

TileMap::TileMap(Vector2 size, shared_ptr<Palette> palette)
	:_mapSize(size), _palette(palette)
{
	_transform = make_shared<Transform>();
	_tileSize = Vector2(30, 30);
	_col = make_shared<RectCollider>(_tileSize);
	_lineRenderer = make_shared<RectLine>(_tileSize);
	_tileRenderer = ADD_TILE(L"Resource/Tile/TileBright.png", _mapSize, _tileSize);

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
	Vector2 worldIndex = GetWorldIndex(mainWorldPos);

	_infos[worldIndex.y][worldIndex.x]->curFrame.x = 1;

	for (int i = -1; i < 2; i++)
	{
		if (worldIndex.y + i < 0 || worldIndex.y + i > _mapSize.y - 1)
			continue;
		for (int j = -1; j < 2; j++)
		{
			if (worldIndex.x + j < 0 || worldIndex.x + j > _mapSize.x - 1)
				continue;
			if (i == 0 && j == 0)
				continue;
			_col->SetPos(_infos[worldIndex.y + i][worldIndex.x + j]->centerPos);
			if (_col->IsCollision(_mainCharacter.lock()->GetCollider()))
			{
				_infos[worldIndex.y + i][worldIndex.x + j]->color = XMFLOAT4(1, 0, 0, 1);
			}
			else
			{
				_infos[worldIndex.y + i][worldIndex.x + j]->color = XMFLOAT4(0, 1, 0, 1);
			}
		}
	}

	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 mouse = CAMERA->GetWorldMousePos();
		Vector2 target = mouse - mainWorldPos;

		float angle = target.Angle() * 57.2958;

		if (angle > -25.0f && angle <= 25.0f)
		{
			_infos[worldIndex.y][worldIndex.x + 1]->curFrame.x++;
		}
		else if (angle > 25.0f && angle <= 70.0f)
		{
			_infos[worldIndex.y + 1][worldIndex.x + 1]->curFrame.x++;
		}
		else if (angle > 70.0f && angle <= 115.0f)
		{
			_infos[worldIndex.y + 1][worldIndex.x]->curFrame.x++;
		}
		else if (angle > 115.0f && angle < 160.0f)
		{
			_infos[worldIndex.y + 1][worldIndex.x - 1]->curFrame.x++;
		}
		else if (angle > -70.0f && angle <= -25.0f)
		{
			_infos[worldIndex.y - 1][worldIndex.x + 1]->curFrame.x++;
		}
		else if (angle > -115.0f && angle <= -70.0f)
		{
			_infos[worldIndex.y - 1][worldIndex.x]->curFrame.x++;
		}
		else if (angle > -160.0f && angle <= -25.0f)
		{
			_infos[worldIndex.y - 1][worldIndex.x - 1]->curFrame.x++;
		}
		else
		{
			_infos[worldIndex.y][worldIndex.x - 1]->curFrame.x++;
		}
	}
}

void TileMap::CreateMap()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 index = GetWorldIndex(W_MOUSE_POS);
		shared_ptr<TileInfo> info = _palette.lock()->GetCurTileInfo();
		if (info == nullptr)
			return;
		_infos[index.y][index.x]->type = info->type;
		_infos[index.y][index.x]->curFrame = info->curFrame;
	}
}

void TileMap::Render()
{
	if (_isDebug)
	{
		for (int i = 0; i < _infos.size(); i++)
		{
			for (int j = 0; j < _infos[i].size(); j++)
			{
				if (_infos[i][j]->type == TileInfo::Type::NONE)
				{
					_col->SetPos(_infos[i][j]->centerPos);
					_col->Update();
					_col->GetTransform()->Set_World();

					_lineRenderer->SetColor(_infos[i][j]->color);
					_lineRenderer->Render();

					continue;
				}
				_col->SetPos(_infos[i][j]->centerPos);
				_col->Update();
				_col->GetTransform()->Set_World();

				_tileRenderer.lock()->SetCurFrame(_infos[i][j]->curFrame);
				_tileRenderer.lock()->Update();
				_tileRenderer.lock()->Render();
				_lineRenderer->SetColor(_infos[i][j]->color);
				_lineRenderer->Render();
			}
		}
	}
	else
	{
		for (int i = 0; i < _infos.size(); i++)
		{
			for (int j = 0; j < _infos[i].size(); j++)
			{
				_transform->SetPos(_infos[i][j]->centerPos);
				_transform->Update();
				_transform->Set_World();
				_tileRenderer.lock()->SetCurFrame(_infos[i][j]->curFrame);
				_tileRenderer.lock()->Update();
				_tileRenderer.lock()->Render();
			}
		}
	}
	
}

void TileMap::SetCameraRange()
{
	float Xhalf = (_mapSize.x * _tileSize.x) / 2 - _tileSize.x / 2;
	float Yhalf = (_mapSize.y * _tileSize.y) / 2 - _tileSize.y / 2;
	CAMERA->SetLeftBottom(Vector2(-Xhalf + WIN_WIDTH / 2, -Yhalf + WIN_HEIGHT / 2));
	CAMERA->SetRightTop(Vector2(Xhalf - WIN_WIDTH / 2, Yhalf - WIN_HEIGHT / 2));
}

Vector2 TileMap::GetWorldIndex(Vector2 pos)
{
	pos.x /= _tileSize.x;
	pos.y /= _tileSize.y;

	float tmpX = _mapSize.x / 2 + 0.5f;
	float tmpY = _mapSize.y / 2 + 0.5f;

	pos.x += tmpX;
	pos.y += tmpY;

	return pos;
}

void TileMap::CreateTileInfos()
{
	Vector2 startPos;
	startPos.x = -(_tileSize.x * (_mapSize.x / 2));
	startPos.y = -(_tileSize.y * (_mapSize.y / 2));

	for (int i = 0; i < _mapSize.y; i++)
	{
		vector<shared_ptr<TileInfo>> tmp;

		for (int j = 0; j < _mapSize.x; j++)
		{
			Vector2 centerPos = Vector2(startPos.x + _tileSize.x * j, startPos.y + _tileSize.y * i);
			shared_ptr<TileInfo> info = make_shared<TileInfo>(centerPos, Vector2(0, 0), TileInfo::Type::NONE);
			tmp.push_back(info);
		}
		_infos.push_back(tmp);
	}
}

void TileMap::ReadFile(wstring path)
{
	//todo : 파일 읽어서 타입 저장
	Vector2 startPos;
	startPos.x = -(_tileSize.x * (_mapSize.x / 2));
	startPos.y = -(_tileSize.y * (_mapSize.y / 2));

	for (int i = 0; i < _mapSize.y; i++)
	{
		vector<shared_ptr<TileInfo>> tmp;

		for (int j = 0; j < _mapSize.x; j++)
		{
			Vector2 centerPos = Vector2(startPos.x + _tileSize.x * j, startPos.y + _tileSize.y * i);
			shared_ptr<TileInfo> info = make_shared<TileInfo>(centerPos, Vector2(0, 6), TileInfo::Type::NONE);
			tmp.push_back(info);
		}
		_infos.push_back(tmp);
	}
}
