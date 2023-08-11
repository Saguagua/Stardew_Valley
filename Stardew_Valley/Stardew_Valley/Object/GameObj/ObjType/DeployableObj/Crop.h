#pragma once
class Crop : public DeployableObject
{
public:
	Crop() :DeployableObject(ObjectInfo::Type::CROP) {}
	~Crop() {}


	void Update();

	virtual void Interaction() override;
	virtual void Spawn(string name, vector<short> vals) override;

	void Watering() {}
	
	void SetPeriod(short period) { _period = period; }
	void SetProgress(short progress) { _progress = progress; }
	void SetQuality(short quality) { _quality = quality; }

private:
	short _period;
	short _progress;
	short _quality;
};

