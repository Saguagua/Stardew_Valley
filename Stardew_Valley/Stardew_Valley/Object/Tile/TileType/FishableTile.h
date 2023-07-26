#pragma once
class FishableTile : public Tile
{
public:
	FishableTile(Vector2 pos, int tileCode, int objCode)
		:Tile(pos, tileCode, objCode) {}
	virtual ~FishableTile() {}

	virtual void Interaction() override;
};

