#pragma once
class Tile
{
public:
	Tile(string name, Vector2 pos);
	~Tile() {}

	Vector2 GetCenterPos() { return _centerPos; }

	void SetCenterPos(Vector2 pos) { _centerPos = pos; }
	
	virtual void Interaction() {}

private:
	string _tileName;
	Vector2 _centerPos;
};