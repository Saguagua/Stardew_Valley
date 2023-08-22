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
		if (_minute == MAXMINUTE) //10
		{
			_hour++;
			_minute = 0;

			if (_hour > MAXHOUR) //24
			{
				PlayerUI::GetInstance()->NextDay();
				ObjectSpawner::GetInstance()->Update_Crops();
				_hour = 6;
			}
		}
	}

	_runTime += _deltaTime;
}
