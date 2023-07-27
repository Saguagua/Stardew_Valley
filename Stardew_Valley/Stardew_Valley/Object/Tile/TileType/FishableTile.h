#pragma once
class FishableTile : public Tile
{
public:
	FishableTile(Vector2 pos, int tileCode, int bitFlag, int objCode)
		:Tile(pos, tileCode, bitFlag, objCode) {}
	virtual ~FishableTile() {}

	virtual void Interaction() override;
};

