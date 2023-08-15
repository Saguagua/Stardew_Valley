#pragma once
class Tile
{
public:
	Tile(string name, Vector2 pos);

	~Tile() {}

	string GetName() { return _tileName; }
	Vector2 GetCenterPos() { return _centerPos; }
	shared_ptr<DeployableObject> GetObj() { return _obj; }
	string GetObjName() { return _objName; }

	void SetName(string name) { _tileName = name; }
	void SetCenterPos(Vector2 pos) { _centerPos = pos; }
	void SetObjName(string name) { _objName = name; }
	void SetObj(shared_ptr<DeployableObject> obj) { _obj = obj; }
	
	virtual void Interaction();

protected:
	string _tileName;
	string _objName;
	Vector2 _centerPos;

	shared_ptr<DeployableObject> _obj;
};