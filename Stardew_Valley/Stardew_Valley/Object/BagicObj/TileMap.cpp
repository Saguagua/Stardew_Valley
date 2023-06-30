#include "framework.h"
#include "TileMap.h"
#include "../Character/Character.h"

TileMap::TileMap(Vector2 size, wstring path, shared_ptr<Character> mainCharacter)
	:_mapSize(size), _mainCharacter(mainCharacter)
{
	_transform = make_shared<Transform>();
	_tileSize = Vector2(30 , 30);
	_lineRenderer = make_shared<RectLine>(_tileSize);
	_quad = make_shared<Quad>(path, Vector2(17, 32), _tileSize);
	
	CreateTiles();
}

void TileMap::Update()
{
	if (!_isActive)
		return;

	Vector2 mainWorldPos = _mainCharacter.lock()->GetTransform()->GetWorldPos();
	Vector2 worldIndex = GetWorldIndex(mainWorldPos);

	_infos[worldIndex.y][worldIndex.x]->curClip.x = 1;

	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 mouse = CAMERA->GetWorldMousePos();
		Vector2 target = mouse - mainWorldPos;

		float angle = target.Angle() * 57.2958;

		if (angle > -25.0f && angle <= 25.0f)
		{
			_infos[worldIndex.y][worldIndex.x + 1]->curClip.x++;
		}
		else if (angle > 25.0f && angle <= 70.0f)
		{
			_infos[worldIndex.y + 1][worldIndex.x + 1]->curClip.x++;
		}
		else if (angle > 70.0f && angle <= 115.0f)
		{
			_infos[worldIndex.y + 1][worldIndex.x]->curClip.x++;
		}
		else if (angle > 115.0f && angle < 160.0f)
		{
			_infos[worldIndex.y + 1][worldIndex.x - 1]->curClip.x++;
		}
		else if (angle > -70.0f && angle <= -25.0f)
		{
			_infos[worldIndex.y - 1][worldIndex.x + 1]->curClip.x++;
		}
		else if (angle > -115.0f && angle <= -70.0f)
		{
			_infos[worldIndex.y - 1][worldIndex.x]->curClip.x++;
		}
		else if (angle > -160.0f && angle <= -25.0f)
		{
			_infos[worldIndex.y - 1][worldIndex.x - 1]->curClip.x++;
		}
		else
		{
			_infos[worldIndex.y][worldIndex.x - 1]->curClip.x++;
		}
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
				_transform->SetPos(_infos[i][j]->centerPos);
				_transform->Update();
				_transform->Set_World();
				_quad->SetCurFrame(_infos[i][j]->curClip);
				_quad->Update();
				_quad->Render();
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
				_quad->SetCurFrame(_infos[i][j]->curClip);
				_quad->Update();
				_quad->Render();
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

void TileMap::CreateTiles()
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
			shared_ptr<TileInfo> info = make_shared<TileInfo>(centerPos, Vector2(0, 6), Type::NONE);
			tmp.push_back(info);
		}

		_infos.push_back(tmp);
	}

}
