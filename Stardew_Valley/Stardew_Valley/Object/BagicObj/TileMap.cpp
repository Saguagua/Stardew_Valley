#include "framework.h"
#include "RectLine.h"
#include "CircleLine.h"
#include "TileMap.h"

TileMap::TileMap(Vector2 size, wstring path)
	:_mapSize(size)
{
	_transform = make_shared<Transform>();
	_tileSize = Vector2(50 , 50);
	_tile = make_shared<RectLine>(_tileSize);
	_circle = make_shared<CircleLine>(50);
	_beachQuad = make_shared<Quad>(L"Resource/Tile/spring_beach.png", Vector2(17, 32), _tileSize);
	_springOutdoorQuad = make_shared<Quad>(L"Resource/Tile/spring_outdoors.png", Vector2(25, 79), _tileSize);
	CreateTiles();
}

void TileMap::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 mouse  = CAMERA->GetWorldMousePos();
		Vector2 mouse2 = CAMERA->GetWorldMousePos();
		mouse.x /= 50;
		mouse.y /= 50;

		_infos[mouse.y + 25][mouse.x + 25].curClip.y++;
	}
}

void TileMap::Render()
{
	for (int i = 0; i < _infos.size(); i++)
	{
		for (int j = 0; j < _infos[i].size(); j++)
		{
			_transform->SetPos(_infos[i][j].centerPos);
			_transform->Update();
			_transform->Set_World();
			_springOutdoorQuad->SetCurFrame(_infos[i][j].curClip);
			_springOutdoorQuad->Update();
			_springOutdoorQuad->Render();

			_tile->Render();
		}
	}
			
}

void TileMap::CreateTiles()
{
	//todo : 파일 읽어서 타입 저장
	for (int i = 0; i < _mapSize.y; i++)
	{
		vector<TileInfo> tmp;

		for (int j = 0; j < _mapSize.x; j++)
		{
			TileInfo info;
			info.centerPos = Vector2(-1225 + 50 * j, -1225 + 50 * i);
			info.curClip = { 0, 6 };
			tmp.push_back(info);
		}

		_infos.push_back(tmp);
	}

}
