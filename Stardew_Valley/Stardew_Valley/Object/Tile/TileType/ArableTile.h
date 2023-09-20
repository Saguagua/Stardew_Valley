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

	~ArableTile() {}

	virtual void Render(shared_ptr<Sprite> renderer, shared_ptr<RectCollider> col) override;

	void SetPlantable(bool val) { _plantable = val; }

	bool GetPlantable() { return _plantable; }
	Connect& GetConnect() { return _connect; }

private:
	Connect _connect;
	bool _plantable = false;
};

