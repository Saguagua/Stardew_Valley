#include "framework.h"
#include "Program.h"
#include "../Scene/TestScene/TestScene.h"
#include "../Scene/TestScene/ColliderScene.h"
#include "../Scene/MapTool/MapToolScene.h"

bool Program::_debug = false;

Program::Program()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	Initialize();

	TIMER->LockRunTime(60);
	CAMERA->SetViewPort(WIN_WIDTH, WIN_HEIGHT);
	Font::GetInstance()->Add("Nanum", L"Nanum NeuRisNeuRisCe", XMFLOAT3(1.0f, 1.0f, 1.0f), 40.0f);
	//Font::GetInstance()->Add("D2Coding", L"D2Coding");
	LightManager::Create();
	ObjectSpawner::Create();
	SoundManager::Create();
	SceneManager::Create();
	//SCENEMANAGER->
}

Program::~Program()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SceneManager::Delete();
	SoundManager::Delete();
	ObjectSpawner::Delete();
	LightManager::Delete();
	Font::Delete();
}

void Program::Update()
{
	TIMER->Update();
	CAMERA->Update();

	InputManager::GetInstance()->Update();
	OBJECT_SPAWNER->Update();
	SCENEMANAGER->Update();
	SOUND->Update();

}

void Program::Render()
{
	Device::GetInstance()->Clear();

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	CAMERA->SetViewBuffer();
	CAMERA->SetProjectionBuffer();

	ALPHA->SetState();

	Font::GetInstance()->GetDC()->BeginDraw();

	SCENEMANAGER->Render();
	OBJECT_SPAWNER->Render();
	CAMERA->SetPostViewPort();

	SCENEMANAGER->PostRender();
	CAMERA->PostRender();
	TIMER->PostRender();


	Font::GetInstance()->GetDC()->EndDraw();


	ImGui::Checkbox("ColliderArea", &Collider::_isDebug);
	// Rendering
	ImGui::Render();
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

	ADD_SRV(XMLPATH1);
	ADD_SRV(XMLPATH2);
	ADD_SRV(XMLPATH3);
	ADD_SRV(XMLPATH4);
	ADD_SRV(XMLPATH5);
	ADD_SRV(XMLPATH6);
	ADD_SRV(XMLPATH7);
}
