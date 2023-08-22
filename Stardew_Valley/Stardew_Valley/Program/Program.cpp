#include "framework.h"
#include "Program.h"
#include "../Scene/TestScene/TestScene.h"
#include "../Scene/TestScene/ColliderScene.h"
#include "../Scene/MapTool/MapToolScene.h"

Program::Program()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	Initialize();
	_scene = make_shared<TestScene>();
	TIMER->LockRunTime(60);
	CAMERA->SetViewPort(WIN_WIDTH, WIN_HEIGHT);
}

Program::~Program()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
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

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Rendering
	ImGui::Render();

	CAMERA->SetViewBuffer();
	CAMERA->SetProjectionBuffer();

	ALPHA->SetState();

	_scene->Render();

	CAMERA->SetPostViewPort();

	_scene->PostRender();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}

void Program::Initialize()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(_hWnd);
	ImGui_ImplDX11_Init(DEVICE.Get(), DC.Get());
}
