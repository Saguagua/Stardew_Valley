#pragma once

class GameObject
{
public:
	GameObject(string name):_name(name){}
	virtual ~GameObject() {}

	string GetName() { return _name; }
	int GetIndex() { return _index; }

	void SetName(string name) { _name = name; }
	bool IsActive() { return _isActive; }
protected:
	string _name;
	bool _isActive = true;
	int _index = 0;
};

