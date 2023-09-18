#pragma once
#define WIN_HEIGHT	720
#define WIN_WIDTH	1280

#define CENTER			Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define PI				3.141592f

#define RED				XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN			XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE			XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
#define PURPLE			XMFLOAT4(0.2f, 0.2f, 1.0f, 1.0f)
#define LIGHTPURPLE		XMFLOAT4(0.4f, 0.4f, 1.0f, 1.0f)
#define GRAY			XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f)
#define BLACK			XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
#define WHITE			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
#define INVISIBLE		XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f)

#define DEVICE			Device::GetInstance()->GetDevice()
#define DC				Device::GetInstance()->GetContext()

#define CAMERA			Camera::GetInstance()

#define DATA			DataManager::GetInstance()

#define TIMER			Timer::GetInstance()
#define DELTA_TIME		Timer::GetInstance()->GetDeltaTime()
#define FPS				Timer::GetInstance()->GetFPS()
#define RUNTIME			Timer::GetInstance()->GetRunTime()
#define MAXHOUR			24
#define MAXMINUTE		10
#define SUNSET			14

#define MAP_SIZE		Vector2(50, 50)
#define TILE_SIZE		Vector2(40, 40)

#define SCENEMANAGER    SceneManager::GetInstance()
#define PLAYERUI		PlayerUI::GetInstance()
#define OBJECT_SPAWNER		ObjectSpawner::GetInstance()
#define MONSTER_SPAWNER		MonsterSpawner::GetInstance()
#define MONEYMANAGER	MoneyManager::GetInstance()
#define EFFECT			EffectManager::GetInstance()
#define SOUND			SoundManager::GetInstance()

#define PALETTE			Palette::GetInstance()

#define MOUSE_POS		InputManager::GetInstance()->GetMousePos()
#define W_MOUSE_POS		Camera::GetInstance()->GetWorldMousePos()
#define S_MOUSE_POS		Camera::GetInstance()->GetScreenMousePos()
#define MOUSE_SCROLL	InputManager::GetInstance()->GetMouseScroll()

#define KEY_UP(k)		InputManager::GetInstance()->Up(k)
#define KEY_PRESS(k)	InputManager::GetInstance()->Press(k)
#define KEY_DOWN(k)		InputManager::GetInstance()->Down(k)

#define ADD_VS(k)		ShaderManager::GetInstance()->Add_Vs(k)
#define ADD_PS(k)		ShaderManager::GetInstance()->Add_Ps(k)

#define ALPHA			StateManager::GetInstance()->GetAlpha()
#define ADDITIVE		StateManager::GetInstance()->GetAdditive()
#define BLEND			StateManager::GetInstance()->GetBlend()
#define SAMPLER			StateManager::GetInstance()->GetSampler()

#define ADD_SRV(k)		SRVManager::GetInstance()->AddSRV(k)
#define ADD_SRV_SIZE(p, s)		SRVManager::GetInstance()->AddSRV(p, s)

#define ADD_TILE(path, frame, size)		TileManager::GetInstance()->GetTile(path, frame, size);

#define CallBack		function<void()>
#define CallBackInt		function<void(int)>
#define CallBackBool	function<void(bool)>

#define GRAVITY			9.8f

#define XMLCOUNT			6

#define XMLPATH1			L"Resource/XMLResource1.png"
#define XMLPATH2			L"Resource/XMLResource2.png"
#define XMLPATH3			L"Resource/XMLResource3.png"
#define XMLPATH4			L"Resource/XMLResource4.png"
#define XMLPATH5			L"Resource/XMLResource5.png"
#define XMLPATH6			L"Resource/XMLResource6.png"