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

	void Update();

	void Set_Shader()
	{
		_posBuffer->Set_VS(3);
		_colorBuffer->Set_PS(1);
	}

	void SetLight(shared_ptr<class LightInfo> info);

	void DisableLight(int index)
	{
		_posBuffer->GetPoses()[index] = { 0,0,0,0 };
		_colorBuffer->GetColors()[index] = { 0,0,0,0 };
	}


private:
	static LightManager* _instance;
	shared_ptr<LightPosBuffer> _posBuffer;
	shared_ptr<LightColorBuffer> _colorBuffer;
	float _timer = 0;
};

