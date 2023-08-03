#include "framework.h"
#include "../../Object/BasicObj/LightTextureRect.h"
#include "LightTestScene.h"

LightTestScene::LightTestScene()
{
	ObjectSpawner::Create();
	renderer = make_shared<LightTextureRect>(L"Resource/Tile/Tile.png", DATA->GetTileMaxFrame(), Vector2(100, 100));
	trenderer = make_shared<TextureRect>(L"Resource/Tile/Tile.png", DATA->GetTileMaxFrame(), Vector2(100, 100));
	
	collider1 = make_shared<CircleCollider>(60);
	collider2 = make_shared<CircleCollider>(60);
	collider3 = make_shared<CircleCollider>(60);
	collider4 = make_shared<CircleCollider>(60);
	collider1->SetDebug(true);
	collider2->SetDebug(true);
	collider3->SetDebug(true);
	collider4->SetDebug(true);
	collider1->SetPos(Vector2(60,60));
	collider2->SetPos(Vector2(WIN_WIDTH - 60, 60));
	collider3->SetPos(Vector2(WIN_WIDTH - 60,WIN_HEIGHT - 60));
	collider4->SetPos(Vector2(60, WIN_HEIGHT - 60));
}

LightTestScene::~LightTestScene()
{
	ObjectSpawner::Delete();
}

void LightTestScene::Update()
{
	
	collider1->Update();
	collider2->Update();
	collider3->Update();
	collider4->Update();
}

void LightTestScene::Render()
{
	collider1->Render();
	collider2->Render();
	collider3->Render();
	collider4->Render();
	renderer->Render();
	//trenderer->Render();
}
