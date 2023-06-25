#include "framework.h"
#include "Tile.h"
#include "TileMap.h"

TileMap::TileMap(Vector2 size, wstring path)
	:_mapSize(size)
{
	Vector2 clientSize = Device::GetInstance()->GetClientSize();
	_transform = make_shared<Transform>();
	_tileSize = Vector2(WIN_WIDTH / _mapSize.x , WIN_HEIGHT / _mapSize.y);
	_tile = make_shared<Tile>(_tileSize);
}

void TileMap::Update()
{
	_tile->Update();
}

void TileMap::Render()
{
	_tile->Render();
}

void TileMap::CreateTiles()
{
	//todo : 파일 읽어서 타입 저장
	
}
