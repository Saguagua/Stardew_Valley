#include "framework.h"
#include "../../Data/LightInfo.h"
#include "LightManager.h"

LightManager* LightManager::_instance = nullptr;

LightManager::LightManager()
{
	_colorBuffer = make_shared<LightColorBuffer>();
	_posBuffer = make_shared<LightPosBuffer>();
	XMFLOAT4* poses = _posBuffer->GetPoses();
	XMFLOAT4* colors = _colorBuffer->GetColors();
	poses[0] = { 60, 60, 0, 0 };
	poses[1] = { WIN_WIDTH - 60, 60, 0, 0 };
	poses[2] = { WIN_WIDTH - 60, WIN_HEIGHT - 60, 0, 0 };
	poses[3] = { 60, WIN_HEIGHT - 60, 0, 0 };
	poses[4] = { 60, 60, 0, 0 };

	colors[0] = { 0.1, 0.1, 0.1, 1 };
	colors[1] = { 10000, 0, 0, 1 };
	colors[2] = { 0, 10000, 0, 1 };
	colors[3] = { 0, 0, 10000, 1 };
	colors[4] = { 1000, 1000, 1000, 1 };

	_colorBuffer->Update();
	_posBuffer->Update();
}

void LightManager::Update()
{
	int hour = TIMER->GetHour();
	//-0.15
	if (hour == 6)
		_colorBuffer->GetSun() = { 0.8f, 0.8f, 0.8f, 1.0f };
	else if (hour < 14)
		_colorBuffer->GetBrighter({ 0.0114f * DELTA_TIME, 0.0114f * DELTA_TIME, 0.0114f * DELTA_TIME, 0 });
	else
	{
		_colorBuffer->GetDarker({ 0.045f * DELTA_TIME, 0.045f * DELTA_TIME, 0.045f * DELTA_TIME, 0 });
	}

	_colorBuffer->Update();
}

void LightManager::SetLight(shared_ptr<LightInfo> info)
{
	XMFLOAT4* pos = _posBuffer->GetPoses();
	XMFLOAT4* color = _colorBuffer->GetColors();

	for (int i = 0; i < 4; i++)
	{
		if (pos[i].x + pos[i].y + pos[i].z < 0)
		{
			pos[i] = info->GetPos();
			color[i] = info->GetColor();
		}
	}
}
