#pragma once
class Crop;

class ArableTile : public Tile
{
public:
	ArableTile(string name, Vector2 pos)
		:Tile(name, pos) 
	{
	}

	virtual ~ArableTile() {}

	void SetPlantable(bool val) { _plantable = val; }
	weak_ptr<Crop> GetCrop() { return _crop; }
	virtual void Interaction() override;

private:
	weak_ptr<Crop> _crop;
	bool _plantable;
};

