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
	void PostRender();

	int GetFPS() { return _frameRate; }
	float GetDeltaTime() { return _deltaTime; }
	float GetRunTime() { return _runTime; }
	void LockRunTime(float val) { _lockFPS = val; }

	int& GetMaxHour() { return _maxHour; }
	int& GetMaxMinute() { return _maxMinute; }
	int& GetHour() { return _hour; }
	int& GetMinute() { return _minute; }

	int GetDayTime() { return _hour < 17.0f ? 0 : 1; }

	void SetNextDay();
private:
	static Timer* _instance;

	float _timeScale = 0.0;
	float _deltaTime = 0.0;

	unsigned __int64 _curTime = 0;
	unsigned __int64 _lastTime = 0;
	unsigned __int64 _periodFrequency = 0;

	unsigned int _frameRate = 0;
	unsigned int _frameCount = 0; //업데이트 빈도

	float _oneSecCount = 0.0;
	float _runTime = 0.0;
	float _lockFPS = 0.0;
	int _hour = 6;
	int _minute = 0;
	int _maxMinute = 6;
	int _maxHour = 24;

	bool _dayTime = true;
};

