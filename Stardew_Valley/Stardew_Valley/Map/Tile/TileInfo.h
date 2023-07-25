#pragma once
class TileInfo
{
public:
	TileInfo(Vector2 pos, Vector2 tileFrame, Vector2 objFrame);
	TileInfo() {}
	~TileInfo() {}

	Vector2& GetStartPos() { return _startPos; }
	Vector2& GetTileFrame() { return _tileFrame; }
	Vector2& GetObjectFrame() { return _objFrame; }

	void SetStartPos(Vector2 pos) { _startPos = pos; }
	void SetTileFrame(Vector2 frame) { _tileFrame = frame; }
	void SetObjectFrame(Vector2 frame) { _objFrame = frame; }

	void PlayerInteration(shared_ptr<class Player> player);
private:
	Vector2 _startPos;
	Vector2 _tileFrame;
	Vector2 _objFrame;
};