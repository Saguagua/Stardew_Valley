#include "framework.h"
#include "Program.h"
#include "../Scene/InGame/TestScene.h"

Program::Program()
{
	_scene = make_shared<TestScene>();
}

void Program::Update()
{
	InputManager::GetInstance()->Update();
	_scene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();
	Camera::GetInstance()->Update();
	_scene->Render();
	Device::GetInstance()->Present();
}
