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
	poses[0] = { 0, 0, 0, 0 };
	poses[1] = { WIN_WIDTH - 60, 60, 0, 0 };
	poses[2] = { WIN_WIDTH - 60, WIN_HEIGHT - 60, 0, 0 };
	poses[3] = { 60, WIN_HEIGHT - 60, 0, 0 };
	poses[4] = { 60, 60, 0, 0 };

	colors[0] = { 1, 1, 1, 0 };
	colors[1] = { 10000, 10000, 10000, 100000 };
	colors[2] = { 10000, 10000, 10000, 100000 };
	colors[3] = { 10000, 10000, 10000, 100000 };
	colors[4] = { 10000, 10000, 10000, 100000 };

	_colorBuffer->Update();
	_posBuffer->Update();
}

void LightManager::Update()
{
	_timer += DELTA_TIME;
	
	if (_timer > 0.1)
	{
		if (_colorBuffer->GetSun().x < 0.1)
			_colorBuffer->GetSun() = { 1,1,1,0 };
		_colorBuffer->GetDarker({0.01,0.01,0.01,0});
		_timer = 0;
		_colorBuffer->Update();
	}
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
