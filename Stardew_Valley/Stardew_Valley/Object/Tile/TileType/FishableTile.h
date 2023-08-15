#pragma once
class FishableTile : public Tile
{
public:
	FishableTile(string name, Vector2 pos)
		:Tile(name, pos) {}
	virtual ~FishableTile() {}

	virtual void Interaction() override;
};

