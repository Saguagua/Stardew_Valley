#pragma once
class Crop : public DeployableObject
{
public:
	Crop(string name, Vector2 pos, vector<short> vals) 
		:DeployableObject(DeployableObject::Type::CROP, name, pos),
		_period(vals[0]), _progress(vals[1]), _quality(vals[2])
	{
		_imgIndex = vals[3];
	}
	~Crop() {}

	void Update();

	virtual void Interaction() override;
	
	void SetPeriod(short period) { _period = period; }
	void SetProgress(short progress) { _progress = progress; }
	void SetQuality(short quality) { _quality = quality; }
	void SetWater(bool val) { _water = val; }

	short GetPeriod() { return _period; }
	short GetProgress() {return _progress; }
	short GetQuality()	{return _quality; }
	bool GetWater() { return _water; }

	virtual vector<int> GetProperty() override;
private:
	short _period;
	short _progress;
	short _quality;

	bool _water;
	short _waterSave = 0;
	bool _ferti;
};

