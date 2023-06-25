#include "framework.h"
#include "TestScene.h"
#include "../../TileMap/TileMap.h"
#include "../../TileMap/Tile.h"

TestScene::TestScene()
{
	_tileMap = make_shared<TileMap>(Vector2(10, 10));
	_tile = make_shared<Tile>(Vector2(100, 100));
}

void TestScene::Update()
{
	_tile->Update();
}

void TestScene::Render()
{
	_tile->Render();
}
