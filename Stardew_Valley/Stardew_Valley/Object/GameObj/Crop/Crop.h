#pragma once
class Crop
{
public:
	Crop(int dropCode, int period);
	~Crop() {}


	void Update();

	int GetDropCode() { return _dropCode; }

private:
	int _frameIndex;
	int _dropCode;
	int _period;
	int _progress = 0;
	int _quality = 2;

};

