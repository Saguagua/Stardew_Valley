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

	Action(vector<Vector2> indices, Action::Type type = Action::Type::LOOP, float speed = 0.1f)
		:_indices(indices), _repeatType(type), _speed(speed) {}

	~Action() {}

	void Update();

	void Play();
	void Pause(bool val);
	void Stop();
	void Reset();

	Vector2 GetCurFrame() { return _indices[_curAnimationIndex]; }

	void AddMiddleEvent(CallBack cb) { _playEvents.push_back(cb); }
	void AddEndEvent(CallBack cb) { _endEvents.push_back(cb);}
	void SetEndBoolEvent(CallBackBool cb) { _endBoolEvent = cb; }
	void SetEndIntEvent(CallBackInt cb) { _endIntEvent = cb; }

	bool IsPlay() { return _isPlay; }
private:
	string _name;
	
	Type _repeatType;
	bool _isPlay = false;

	vector<Vector2> _indices;

	int _curAnimationIndex = 0;

	float _time = 0.0f;
	float _speed = 0.0f;

	bool _isReverse = false;

	vector<CallBack> _playEvents;
	vector<CallBack> _endEvents;
	CallBackBool _endBoolEvent = nullptr;
	CallBackInt _endIntEvent = nullptr;
};

