#pragma once
#define WIN_HEIGHT	720
#define WIN_WIDTH	1280


#define CENTER Vector2(WIN_WIDTH * 0.5g, WIN_HEIGHT * 0.5f)

#define GREEN		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)

#define DEVICE		Device::GetInstance()->GetDevice()
#define DC			Device::GetInstance()->GetContext()

#define ADD_VS(k)	ShaderManager::GetInstance()->Add_Vs(k)
#define ADD_PS(k)	ShaderManager::GetInstance()->Add_Ps(k)