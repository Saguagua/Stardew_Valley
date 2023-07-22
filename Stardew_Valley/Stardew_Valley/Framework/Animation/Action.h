#pragma once
class Action
{
public:
	
	enum Type
	{
		END,
		LOOP,
		PINGPONG
	};

	Action(int start, int end, int y, Action::Type type = Action::Type::LOOP, float speed = 0.1f)
		:_start(start), _end(end), _y(y), _repeatType(type), _speed(speed) {}
	~Action() {}

	void Update();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	Vector2 GetCurFrame() { return Vector2(_curAnimationIndex, _y); }

	void SetEndEvent(CallBack cb) { _endEvent = cb; }

private:
	string _name;
	
	Type _repeatType;
	bool _isPlay = false;

	int _start;
	int _end;
	int _curAnimationIndex = 0;
	int _y;

	float _time = 0.0f;
	float _speed = 0.0f;

	bool _isReverse = false;

	CallBack _endEvent = nullptr;
};

