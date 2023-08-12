#pragma once
class FishableTile : public Tile
{
public:
	FishableTile(string name, Vector2 pos, string objName)
		:Tile(name, pos, objName) {}
	virtual ~FishableTile() {}

	virtual void Interaction() override;
};

