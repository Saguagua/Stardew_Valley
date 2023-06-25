#include "framework.h"
#include "Program.h"
#include "../Scene/InGame/TestScene.h"

Program::Program()
{
	_scene = make_shared<TestScene>();
	_view = make_shared<MatrixBuffer>();
	_proj = make_shared<MatrixBuffer>();

	_view->Update();
	XMMATRIX tmp = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);
	_proj->SetMatrix(tmp);
	_proj->Update();
	
}

void Program::Update()
{
	_scene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();
	_view->Set_VS(1);
	_proj->Set_VS(2);
	_scene->Render();
	Device::GetInstance()->Present();
}
