#pragma once
class Tile
{
public:
	Tile(string name, Vector2 pos, string objName);

	~Tile() {}

	string GetName() { return _tileName; }
	Vector2 GetCenterPos() { return _centerPos; }
	shared_ptr<DeployableObject> GetObj() { return _obj; }
	string GetObjName() { return _obj->GetName(); }

	void SetName(string name) { _tileName = name; }
	void SetCenterPos(Vector2 pos) { _centerPos = pos; }
	
	virtual void Interaction();

protected:
	string _tileName;
	Vector2 _centerPos;

	shared_ptr<DeployableObject> _obj;
};