#include "framework.h"
#include "LightManager.h"

LightManager* LightManager::_instance = nullptr;

LightManager::LightManager()
{
	_sunLight = { 0.8f, 0.8f, 0.8f, 1.0f };
	

	/*
	XMFLOAT4* poses = _posBuffer->GetPoses();
	XMFLOAT4* colors = _colorBuffer->GetColors();

	poses[0] = { 60, 60, 0, 0 };
	poses[1] = { WIN_WIDTH - 60, 60, 0, 0 };
	poses[2] = { WIN_WIDTH - 60, WIN_HEIGHT - 60, 0, 0 };
	poses[3] = { 60, WIN_HEIGHT - 60, 0, 0 };
	poses[4] = { 60, 60, 0, 0 };

	colors[1] = { 10000, 0, 0, 1 };
	colors[2] = { 0, 10000, 0, 1 };
	colors[3] = { 0, 0, 10000, 1 };
	colors[4] = { 1000, 1000, 1000, 1 };
	*/
}

void LightManager::UpdateSun()
{
	if (_mapToolMode)
		_sunLight = { 1.0f, 1.0f, 1.0f, 1.0f };
	else if (!_sunOn)
		_sunLight = {0.1f, 0.1f, 0.1f, 1.0f};
	else
	{
		if (_hour < SUNSET)
		{
			float normalValue = 0.2f / ((SUNSET - 6) * _maxMinute);
			int curTime = (_hour - 6) * _maxMinute + _minute;
			float val = 0.8f + normalValue * curTime;

			_sunLight = { val, val, val, 1.0f };
		}
		else
		{
			float normalValue = 0.995f / ((_maxHour - SUNSET) * _maxMinute);
			int curTime = (_hour - SUNSET) * _maxMinute + _minute;
			float val = 1.0f - normalValue * curTime;

			_sunLight = { val, val, val, 1.0f };
		}
	}

	_colorBuffer->SetSun(_sunLight);
	_colorBuffer->Update();
}

