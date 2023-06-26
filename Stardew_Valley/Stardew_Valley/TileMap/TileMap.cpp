#include "framework.h"
#include "Tile.h"
#include "TileMap.h"

TileMap::TileMap(Vector2 size, wstring path)
	:_mapSize(size)
{
	_transform = make_shared<Transform>();
	_tileSize = Vector2(50 , 50);
	_tile = make_shared<Tile>(_tileSize);
	_beachQuad = make_shared<Quad>(L"Resource/Tile/spring_beach.png", Vector2(17, 32), _tileSize);
	CreateTiles();
}

void TileMap::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 mouse  = MOUSE_POS;
		Vector2 mouse2 = MOUSE_POS;
		mouse.x /= 50;
		mouse.y /= 50;

		int intValue = static_cast<int>(mouse.x); 
		float fractionalPart = mouse.x - intValue;

		if (fractionalPart >= 0.5f)
			mouse.x++;
		else if (fractionalPart <= -0.5f)
			mouse.x;


		intValue = static_cast<int>(mouse.y);
		fractionalPart = mouse.y - intValue;

		if (fractionalPart >= 0.5f)
			mouse.y++;
		else if (fractionalPart <= -0.5f)
			mouse.y;

		_infos[mouse.y-1][mouse.x-1].curClip.y++;
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
			_beachQuad->SetCurFrame(_infos[i][j].curClip);
			_beachQuad->Update();
			_beachQuad->Render();
			_tile->Update();
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
			info.centerPos = Vector2(50 + 50 * j, 50 + 50 * i);
			tmp.push_back(info);
		}

		_infos.push_back(tmp);
	}

}
