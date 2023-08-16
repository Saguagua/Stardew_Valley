#pragma once
class Tile
{
public:
	Tile(string name, Vector2 pos);

	virtual ~Tile() {}

	virtual void Render(shared_ptr<class Sprite> renderer);

	string GetName() { return _tileName; }
	Vector2 GetCenterPos() { return _centerPos; }
	bool IsFocus() { return _onFocus; }
	shared_ptr<DeployableObject> GetObj() { return _obj; }
	string GetObjName() { return _objName; }

	void SetName(string name) { _tileName = name; }
	void SetCenterPos(Vector2 pos) { _centerPos = pos; }
	void SetFocus(bool val) { _onFocus = val; }
	void SetObjName(string name) { _objName = name; }
	void SetObj(shared_ptr<DeployableObject> obj) { _obj = obj; }

protected:
	string _tileName;
	string _objName;
	Vector2 _centerPos;
	bool _onFocus = false;

	shared_ptr<DeployableObject> _obj;
};