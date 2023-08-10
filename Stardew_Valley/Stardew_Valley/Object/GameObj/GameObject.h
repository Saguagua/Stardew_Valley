#pragma once
#include "../../Data/ObjectInfo.h"

class GameObject
{
public:
	GameObject(int objCode, int frameIndex, short maxCount, short count = 1)
		:_objCode(objCode), _frameIndex(frameIndex), _maxCount(maxCount), _count(count) {}
	GameObject(int objCode, int frameIndex)
		:_objCode(objCode), _frameIndex(frameIndex), _maxCount(0), _count(0)
	{
		_type = ObjectInfo::Type::BLANK;
	}

	~GameObject() {}

	bool AddCount();
	void SetCode(int code) { _objCode = code; }
	void SetFrameIndex(int index) { _frameIndex = index; }

	ObjectInfo::Type GetType() { return _type; }
	int GetCode() { return _objCode; }
	int GetFrameIndex() { return _frameIndex; }
	short GetCount() { return _count; }
	
	virtual void Interaction() {};
	virtual void KeyInput() {};

protected:
	ObjectInfo::Type _type = ObjectInfo::Type::NONE;
	int _objCode;
	int _frameIndex;
	short _maxCount;
	short _count;
};

