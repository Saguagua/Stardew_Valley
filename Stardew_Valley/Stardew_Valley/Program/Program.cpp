#include "framework.h"
#include "Program.h"
#include "../Scene/TestScene/TestScene.h"
#include "../Scene/TestScene/ColliderScene.h"

Program::Program()
{
	_scene = make_shared<TestScene>();
	TIMER->LockRunTime(60);
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
	_scene->Render();
	Device::GetInstance()->Present();
}
