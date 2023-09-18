#pragma once
class DeployableObject : public GameObject
{

public:
	enum Type
	{
		BREAK = 0,
		PICK  = 1,
		LIGHT = 2,
		BOX   = 3,
		HOUSE = 4,
		CROP  = 5,
		DROP  = 6,
		WALL  = 7,
		DOOR  = 8,
		BED	  = 9,
		ELEVATOR = 10,
		BLANK = 11
	};

	DeployableObject(DeployableObject::Type type, string name, Vector2 pos);
	virtual ~DeployableObject() {}

	void Render(shared_ptr<class Sprite> renderer, shared_ptr<RectCollider> col);
	
	virtual void Interaction() {}

	void SetActive(bool active) { _isActive = active; }
	void SetType(DeployableObject::Type type) { _type = type; }
	void SetPos(Vector2 pos) { _centerPos = pos; }

	Type GetType() { return _type; }

	virtual vector<int> GetProperty() abstract;
	
	virtual void Update();
protected:
	DeployableObject::Type _type;
	Vector2 _centerPos;
};

