#pragma once
#define WIN_HEIGHT	720
#define WIN_WIDTH	1280

#define CENTER			Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define GREEN			XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)

#define DEVICE			Device::GetInstance()->GetDevice()
#define DC				Device::GetInstance()->GetContext()

#define MOUSE_POS		InputManager::GetInstance()->GetMousePos()
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