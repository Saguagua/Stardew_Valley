#include "framework.h"
#include "LogoScene.h"

LogoScene::LogoScene()
{
	_backGroundSlot = make_shared<Transform>();
	_logoSlot = make_shared<Transform>();
	_logoSlot->SetPos(Vector2(0, 50));

	_backGround = make_shared<Sprite>("StardewPanorama", Vector2(WIN_WIDTH, WIN_HEIGHT), SpriteType::UI);
	_logo = make_shared<Sprite>("Logo", Vector2(600, 400), SpriteType::UI);
	_mapToolBtn = make_shared<TextureButton>("Button", Vector2(150, 100));
	_playBtn = make_shared<TextureButton>("Button", Vector2(150, 100));
	_exitBtn = make_shared<TextureButton>("Button", Vector2(150, 100));

	_mapToolBtn->SetPos(Vector2(-200, -270));
	_mapToolBtn->SetFont(L"맵툴");
	_mapToolBtn->SetFontPos(Vector2(-25, 0));

	_playBtn->SetPos(Vector2(0, -270));
	_playBtn->SetFont(L"플레이");
	_playBtn->SetFontPos(Vector2(-35, 0));

	_exitBtn->SetPos(Vector2(200, -270));
	_exitBtn->SetFont(L"나가기");
	_exitBtn->SetFontPos(Vector2(-30, 0));

	CallBackInt cb1 = std::bind(&LogoScene::SceneChange, this, SceneManager::MAPTOOL);
	CallBackInt cb2 = std::bind(&LogoScene::SceneChange, this, SceneManager::TEST);

	_mapToolBtn->AddPushEvent(cb1);
	_playBtn->AddPushEvent(cb2);

	_cb = std::bind(&LogoScene::WhenCoverDark, this);
}

LogoScene::~LogoScene()
{
}

void LogoScene::Update()
{
	_backGroundSlot->Update();
	_logoSlot->Update();
	_mapToolBtn->Update();
	_playBtn->Update();
	_exitBtn->Update();
}

void LogoScene::Render()
{
}

void LogoScene::Initialize()
{
	LightManager::GetInstance()->_mapToolMode = false;
}

void LogoScene::PostRender()
{
	_backGroundSlot->Set_World();
	_backGround->Render();

	_logoSlot->Set_World();
	_logo->Render();

	_mapToolBtn->PostRender();
	_playBtn->PostRender();
	_exitBtn->PostRender();
}

void LogoScene::SceneChange(int index)
{
	SCENEMANAGER->_cover->FadeStart(_cb, nullptr);
	_nextSceneIndex = index;
}

void LogoScene::WhenCoverDark()
{
	SCENEMANAGER->ChangeScene(_nextSceneIndex);
}
