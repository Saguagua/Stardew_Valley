#include "framework.h"
#include "Timer.h"

Timer* Timer::_instance = nullptr;

Timer::Timer()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

	_timeScale = 1.0f / (float)_periodFrequency;
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	_deltaTime = (float)(_curTime - _lastTime) * _timeScale;

	if (_lockFPS != 0)
	{
		while (_deltaTime < (1.0f / _lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			_deltaTime = (float)(_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;

	_frameCount++;
	_oneSecCount += _deltaTime;

	if (_oneSecCount >= 1)
	{
		_frameRate = _frameCount;
		_oneSecCount = 0;
		_frameCount = 0;

		
		_minute++;
		LightManager::GetInstance()->UpdateSun();
		if (_minute == _maxMinute) //10
		{
			_hour++;
			_minute = 0;

			if (_hour >= _maxHour) //24
			{
				//플레이어 기절 추가
				SetNextDay();
			}
		}
		
	}

	_runTime += _deltaTime;
}

void Timer::PostRender()
{
	if (ImGui::BeginMenu("Time"))
	{
		int hourTmp = _hour;
		int minuteTmp = _minute;
		ImGui::SliderInt("Hour", &hourTmp, 6, _maxHour);
		ImGui::SliderInt("Minute", &minuteTmp, 0, _maxMinute);

		if (hourTmp != _hour || minuteTmp != _minute)
		{
			_hour = hourTmp;
			_minute = minuteTmp;
			LightManager::GetInstance()->UpdateSun();
		}

		ImGui::EndMenu();
	}
}

void Timer::SetNextDay()
{
	_hour = 6;
	_minute = 0;
	OBJECT_SPAWNER->Update_Crops();
}
