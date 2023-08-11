#pragma once
#include "../../Data/ObjectInfo.h"

class GameObject
{
public:
	GameObject(ObjectInfo::Type type)
		:_type(type)
	{}
	
	~GameObject() {}

	bool AddCount();

	ObjectInfo::Type GetType() { return _type; }
	short GetCount() { return _count; }

	void SetName(string name) { _name = name; }

protected:
	ObjectInfo::Type _type = ObjectInfo::Type::NONE;
	string _name;
	short _count;
};

