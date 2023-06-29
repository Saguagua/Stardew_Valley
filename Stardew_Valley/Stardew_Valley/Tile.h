#pragma once
class Tile
{
public:
	enum TileType
	{
		MOVEABLE = (1 << 0),
		BLOCK = (1 << 1),
		FARMING = (1 << 2),
		FISHING = (1 << 3),
		ITEMSETTING = (1 << 4)
	};

	Tile(Vector2 pos, Vector2 clip, BYTE type);
	~Tile() {}

	void SetType(BYTE type) { _type = type; }
	void SetPos(Vector2 pos) { _centerPos = pos; }
	void SetCurClip(Vector2 clip) { _curClip = clip; }

	BYTE GetType() { return _type; }
	Vector2 GetPos() { return _centerPos; }
	Vector2 GetCurClip() { return _curClip; }


private:
	BYTE _type;
	Vector2 _centerPos;
	Vector2 _curClip;
};

