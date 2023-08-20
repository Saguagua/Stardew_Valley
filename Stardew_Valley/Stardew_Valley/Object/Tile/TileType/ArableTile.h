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

	virtual void Render(shared_ptr<Sprite> renderer, shared_ptr<RectCollider> col) override;

	void Plant(string cropName);

	void SetPlantable(bool val) { _plantable = val; }

	bool GetPlantable() { return _plantable; }
	weak_ptr<Crop> GetCrop() { return _crop; }
	Connect& GetConnect() { return _connect; }

	virtual void Interaction() override;

private:
	weak_ptr<Crop> _crop;
	Connect _connect;
	bool _plantable = false;
};

