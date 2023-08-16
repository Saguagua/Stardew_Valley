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

	virtual void Render(shared_ptr<class Sprite> renderer) override;

	void SetPlantable(bool val) { _plantable = val; }
	void SetDritName(string name) { _hoeDirtName = name; }
	weak_ptr<Crop> GetCrop() { return _crop; }
	string GetDirtName() { return _hoeDirtName; }


private:
	weak_ptr<Crop> _crop;
	string _hoeDirtName = "BLANK";
	bool _plantable;
};

