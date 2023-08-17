#pragma once
class Crop;

class ArableTile : public Tile
{
public:
	struct Connect
	{
		bool _up = false;
		bool _down = false;
		bool _left = false;
		bool _right = false;
	};

	ArableTile(string name, Vector2 pos)
		:Tile(name, pos) 
	{
	}

	virtual ~ArableTile() {}

	virtual void Render(shared_ptr<class Sprite> renderer) override;

	void SetWater(bool val) { _water = val; }

	void SetPlantable(bool val) { _plantable = val; }

	weak_ptr<Crop> GetCrop() { return _crop; }
	bool GetPlantable() { return _plantable; }
	Connect& GetConnect() { return _connect; }

private:
	weak_ptr<Crop> _crop;
	Connect _connect;
	bool _plantable = false;
	bool _water = false;
};

