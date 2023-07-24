#include "framework.h"
#include "Action.h"


void Action::Update()
{
	if (_isPlay == false)
		return;

	_time += DELTA_TIME;

	if (_time > _speed)
	{
		_time = 0.0f;

		switch (_repeatType)
		{
		case Action::END:
		{
			_curAnimationIndex++;
			if (_curAnimationIndex >= _indices.size() - 1)
				Stop();
		}
		break;
		case Action::LOOP:
		{
			_curAnimationIndex++;
			_curAnimationIndex %= _indices.size();
		}
		break;
		case Action::PINGPONG:
		{
			if (_isReverse)
			{
				_curAnimationIndex--;
				if (_curAnimationIndex <= 0)
					_isReverse = false;
			}
			else
			{
				_curAnimationIndex++;
				if (_curAnimationIndex >= _indices.size() - 1)
					_isReverse = true;
			}
		}
		break;
		default:
			break;
		}
	}
}

void Action::Play()
{
	_curAnimationIndex = 0;
	_isPlay = true;
	_isReverse = false;
	_time = 0.0f;
}

void Action::Pause()
{
	_isPlay = false;
}

void Action::Stop()
{
	_isPlay = false;
	_time = 0.0f;
	_curAnimationIndex = 0;

	if (_endEvent != nullptr)
		_endEvent();
}

void Action::Reset()
{
	_isPlay = false;
	_curAnimationIndex = 0;
	_time = 0.0f;
}
