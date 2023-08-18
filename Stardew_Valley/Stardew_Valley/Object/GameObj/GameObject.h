#pragma once

class GameObject
{
public:
	GameObject(string name):_name(name){}
	
	virtual ~GameObject() {}

	string GetName() { return _name; }
	void Render(shared_ptr<class Sprite> renderer);

	void SetName(string name) { _name = name; }
	bool IsActive() { return _isActive; }
protected:
	string _name;
	bool _isActive = true;
};

