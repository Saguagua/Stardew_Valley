#pragma once
class DeployableObject;

class Tile
{
public:
	Tile(string name, Vector2 pos);

	virtual ~Tile() {}

	virtual void Render(shared_ptr<class Sprite> renderer, shared_ptr<class RectCollider> transform);

	string GetName() { return _tileName; }
	Vector2 GetCenterPos() { return _centerPos; }
	bool IsFocus() { return _onFocus; }
	shared_ptr<DeployableObject> GetObj() { return _obj; }
	string GetObjName() { return _objName; }
	bool IsBlock();

	void SetName(string name) { _tileName = name; }
	void SetCenterPos(Vector2 pos) { _centerPos = pos; }
	void SetFocus(bool val) { _onFocus = val; }
	void SetObjName(string name) { _objName = name; }
	void SetObj(shared_ptr<DeployableObject> obj) { _obj = obj; }

	void DeleteObj() { _objName = "BLANK"; _obj = nullptr; }

	int _mapIndex;
protected:
	string _tileName;
	string _objName = "BLANK";
	Vector2 _centerPos;
	int _animationIndex;

	bool _onFocus = false;

	shared_ptr<DeployableObject> _obj;
};