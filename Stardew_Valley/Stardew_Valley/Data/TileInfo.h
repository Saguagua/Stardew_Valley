#pragma once
class TileInfo
{
public:
	TileInfo(Vector2 pos, Vector2 tileFrame, Vector2 objFrame);
	TileInfo() {}
	~TileInfo() {}

	Vector2& GetCenterPos() { return _centerPos; }
	Vector2& GetTileFrame() { return _tileFrame; }
	Vector2& GetObjectFrame() { return _objFrame; }

	void SetCenterPos(Vector2 pos) { _centerPos = pos; }
	void SetTileFrame(Vector2 frame) { _tileFrame = frame; }
	void SetObjectFrame(Vector2 frame) { _objFrame = frame; }

	void PlayerInteration(shared_ptr<class Player> player);
private:
	Vector2 _centerPos;
	Vector2 _tileFrame;
	Vector2 _objFrame;
};