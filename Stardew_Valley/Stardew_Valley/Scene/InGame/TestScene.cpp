#include "framework.h"
#include "TestScene.h"
#include "../../TileMap/TileMap.h"
#include "../../TileMap/Tile.h"

TestScene::TestScene()
{
	_tileMap = make_shared<TileMap>(Vector2(100, 100));
}

void TestScene::Update()
{
	_tileMap->Update();
}

void TestScene::Render()
{
	_tileMap->Render();
}
