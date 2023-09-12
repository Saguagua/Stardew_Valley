#pragma once
class LightManager
{
private:
	LightManager();
	~LightManager() {}

public:

	static void Create()
	{
		if (_instance == nullptr)
			_instance = new LightManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static LightManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
	}

	void Set_Shader()
	{
		_posBuffer->Set_VS(3);
		_colorBuffer->Set_PS(1);
	}


	void DisableLight(int index)
	{
		_posBuffer->_lightOn[index] = false;
		_posBuffer->GetPoses()[index] = { 0,0,0,0 };
		_colorBuffer->GetColors()[index + 1] = { 0,0,0,0 };
	}

	void Update();
	void UpdateSun();

	void Set_Light(shared_ptr<LightColorBuffer> color, shared_ptr<LightPosBuffer> pos)
	{
		_colorBuffer = color;
		_posBuffer = pos;
	}

	bool _sunOn = true;

private:
	static LightManager* _instance;
	shared_ptr<LightPosBuffer> _posBuffer;
	shared_ptr<LightColorBuffer> _colorBuffer;
	XMFLOAT4 _sunLight;
	int& _maxHour = TIMER->GetMaxHour();
	int& _maxMinute = TIMER->GetMaxMinute();
	int& _hour = TIMER->GetHour();
	int& _minute = TIMER->GetMinute();
};

