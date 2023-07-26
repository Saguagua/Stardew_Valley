#pragma once
class Tile
{
public:
	enum Type
	{
		NONE,
		BLOCK = (1 << 0),
		FARMING = (1 << 1),
		FISHING = (1 << 2)
	};

	Tile(Vector2 pos, int tileCode, int objCode);
	~Tile() {}

	shared_ptr<GameObject> GetObj() { return _obj; }
	Vector2 GetCenterPos() { return _centerPos; }
	int GetTileCode() { return _tileCode; }
	int GetObjectCode() { return _obj->GetCode(); }
	int GetBitFlag() { return _bitFlag; }

	void SetCenterPos(Vector2 pos) { _centerPos = pos; }
	void SetTileCode(int code) { _tileCode = code; }
	void SetObject(shared_ptr<GameObject> obj) { _obj = obj; }
	void SetObject(int code) { _obj = ObjectSpawner::CreateObj(code); }
	void SetBitFlag(int bitFlag) { _bitFlag = bitFlag; }

private:
	shared_ptr<GameObject> _obj;
	Vector2 _centerPos;
	int _tileCode;
	int _bitFlag = 0;
};

