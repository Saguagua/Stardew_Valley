#pragma once
#include "../../Data/ObjectInfo.h"

class GameObject
{
public:
	GameObject(string name):_name(name){}
	
	virtual ~GameObject() {}

	string GetName() { return _name; }

	void SetName(string name) { _name = name; }
	bool IsActive() { return _isActive; }
protected:
	string _name;
	bool _isActive = true;
};

