#pragma once
class DeployableObject : public GameObject
{

public:
	enum Type
	{
		BREAK = 0,
		PICK = 1,
		LIGHT = 2,
		BOX = 3,
		HOUSE = 4,
		CROP = 5,
		DROP = 6,
		BLOCK = 7,
		BLANK = 8
	};

	DeployableObject(DeployableObject::Type type, string name, Vector2 pos);
	virtual ~DeployableObject() {}

	void Render(shared_ptr<class Sprite> renderer, shared_ptr<RectCollider> col);
	
	virtual void Interaction() abstract;

	void SetActive(bool active) { _isActive = active; }
	void SetType(DeployableObject::Type type) { _type = type; }
	void SetPos(Vector2 pos) { _centerPos = pos; }

	Type GetType() { return _type; }
	
protected:
	DeployableObject::Type _type;
	Vector2 _centerPos;
};

