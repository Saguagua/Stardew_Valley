#pragma once
class Crop : public DeployableObject
{
public:
	Crop(string name, Vector2 pos, short progress, short quality);
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
	short _cropType;

	short _waterSave = 0;
	bool _water = false;
	bool _ferti = false;
};

