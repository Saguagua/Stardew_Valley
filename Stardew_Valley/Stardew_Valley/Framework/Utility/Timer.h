#pragma once
class Timer
{
private:
	Timer();
	~Timer() {}

public:

	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Timer();
	}
	
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Timer* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();

	int GetFPS() { return _frameRate; }
	float GetDeltaTime() { return _deltaTime; }
	float GetRunTime() { return _runTime; }
	void LockRunTime(float val) { _lockFPS = val; }
	int GetHour() { return _hour; }
	int GetMinute() { return _minute; }
	int GetTime() { return _hour * 10 + _minute; }
	int GetDayTime() { return _hour < 17.0f ? 0 : 1; }

	void SetNextDay() { _hour = 6; _minute = 0; }
private:
	static Timer* _instance;

	float _timeScale = 0.0;
	float _deltaTime = 0.0;

	unsigned __int64 _curTime = 0;
	unsigned __int64 _lastTime = 0;
	unsigned __int64 _periodFrequency = 0;

	unsigned int _frameRate = 0;
	unsigned int _frameCount = 0;

	float _oneSecCount = 0.0;
	float _runTime = 0.0;
	float _lockFPS = 0.0;
	int _hour = 6;
	int _minute = 0;

	bool _dayTime = true;
};

