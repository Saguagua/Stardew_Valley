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

#define TIMER			Timer::GetInstance()
#define DELTA_TIME		Timer::GetInstance()->GetDeltaTime()
#define FPS				Timer::GetInstance()->GetFPS()
#define RUNTIME			Timer::GetInstance()->GetRunTime()

#define DATA			DataManager::GetInstance()

#define TILEMAP			TileMap::GetInstance()

#define PLAYER			Player::GetInstance()
#define PLAYERINFO		Player::GetInstance()->GetInfo()

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

#define ADD_SRV(k)		SRVManager::GetInstance()->AddSRV(k);
#define ADD_SRV_SIZE(p, s)		SRVManager::GetInstance()->AddSRV(p, s);

#define ADD_TILE(path, frame, size)		TileManager::GetInstance()->GetTile(path, frame, size);

#define MAP_SIZE		Vector2(50, 50)
#define TILE_SIZE		Vector2(40, 40)
#define SPEED			200.0f

#define CallBack		function<void()>
#define CallBackInt		function<void(int)>
#define CallBackBool	function<void(bool)>