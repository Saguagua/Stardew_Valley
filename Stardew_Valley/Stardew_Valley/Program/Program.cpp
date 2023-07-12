#include "framework.h"
#include "Program.h"
#include "../Scene/TestScene/TestScene.h"
#include "../Scene/TestScene/ColliderScene.h"
#include "../Scene/MapTool/MapToolScene.h"

Program::Program()
{
	_scene = make_shared<MapToolScene>();
	TIMER->LockRunTime(60);
	CAMERA->SetViewPort(WIN_WIDTH, WIN_HEIGHT);
}

void Program::Update()
{
	TIMER->Update();
	CAMERA->Update();

	InputManager::GetInstance()->Update();
	_scene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();
	CAMERA->SetViewBuffer();
	CAMERA->SetProjectionBuffer();
	ALPHA->SetState();
	//ADDITIVE->SetState();
	_scene->Render();
	CAMERA->SetPostViewPort();
	_scene->PostRender();
	Device::GetInstance()->Present();
}
