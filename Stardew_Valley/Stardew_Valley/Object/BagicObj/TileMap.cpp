#include "framework.h"
#include "RectLine.h"
#include "CircleLine.h"
#include "TileMap.h"

TileMap::TileMap(Vector2 size, wstring path)
	:_mapSize(size)
{
	_transform = make_shared<Transform>();
	_tileSize = Vector2(30 , 30);
	_tile = make_shared<RectCollider>(_tileSize);
	_beachQuad = make_shared<Quad>(L"Resource/Tile/spring_beach.png", Vector2(17, 32), _tileSize);
	_springOutdoorQuad = make_shared<Quad>(L"Resource/Tile/spring_outdoors.png", Vector2(25, 79), _tileSize);

	CreateTiles();
}

void TileMap::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 index = GetWorldIndex(CAMERA->GetWorldMousePos());

		_infos[index.y][index.x]->curClip.y++;
	}
}

void TileMap::Render()
{
	for (int i = 0; i < _infos.size(); i++)
	{
		for (int j = 0; j < _infos[i].size(); j++)
		{
			_transform->SetPos(_infos[i][j]->centerPos);
			_transform->Update();
			_transform->Set_World();
			_springOutdoorQuad->SetCurFrame(_infos[i][j]->curClip);
			_springOutdoorQuad->Update();
			_springOutdoorQuad->Render();
			_tile->SetPos(_infos[i][j]->centerPos);
			_tile->Update();
			_tile->Render();
		}
	}
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
