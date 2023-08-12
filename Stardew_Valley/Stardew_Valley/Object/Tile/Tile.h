#pragma once
class Tile
{
public:
	Tile(string name, Vector2 pos, string objName);

	Tile(string name, Vector2 pos)
		:_tileName(name), _centerPos(pos)
	{}
	~Tile() {}

	Vector2 GetCenterPos() { return _centerPos; }

	void SetCenterPos(Vector2 pos) { _centerPos = pos; }
	
	virtual void Interaction();

protected:
	string _tileName;
	Vector2 _centerPos;

	shared_ptr<DeployableObject> _obj;
};