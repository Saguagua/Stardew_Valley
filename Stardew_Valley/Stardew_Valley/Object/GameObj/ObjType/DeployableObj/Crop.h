#pragma once
class Crop : public DeployableObject
{
public:
	Crop(string name, Vector2 size, vector<short> vals) 
		:DeployableObject(DeployableObject::Type::CROP, name, size),
		_period(vals[0]), _progress(vals[1]), _quality(vals[2]), _level(vals[3])
	{}
	~Crop() {}

	void Update();

	virtual void Interaction() override;
	
	void SetPeriod(short period) { _period = period; }
	void SetProgress(short progress) { _progress = progress; }
	void SetQuality(short quality) { _quality = quality; }

	short GetPeriod() { return _period; }
	short GetProgress() {return _progress; }
	short GetQuality()	{return _quality; }
	short GetLevel() { return _level; }

private:
	short _period;
	short _progress;
	short _quality;
	short _level;

};

