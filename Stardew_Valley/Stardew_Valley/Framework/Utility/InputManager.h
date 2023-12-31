#pragma once
#define KEY_MAX 255

class InputManager
{
private:
	enum State
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

	InputManager();
	~InputManager() {}

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new InputManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static InputManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void Update();

	bool Down(UINT key) { return _stateMap[key] == DOWN; }
	bool Up(UINT key) { return _stateMap[key] == UP; }
	bool Press(UINT key) { return _stateMap[key] == PRESS; }

	const Vector2& GetMousePos() { return _mousePos; }
	void SetMousePos(Vector2 pos) { _mousePos = pos; }

	int GetMouseScroll() { return _mouseScroll; }
	void SetMouseScroll(short val) { _mouseScroll = val; }

	bool ScrollUp() { return _mouseScroll > 0; }
	bool ScrollDown() { return _mouseScroll < 0; }
private:
	static InputManager* _instance;

	byte _curState[KEY_MAX] = {};
	byte _oldState[KEY_MAX] = {};
	byte _stateMap[KEY_MAX] = {};

	Vector2 _mousePos;
	short _mouseScroll = 0;
};

