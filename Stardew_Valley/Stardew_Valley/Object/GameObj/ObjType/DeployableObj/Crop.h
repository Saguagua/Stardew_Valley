#pragma once
class Crop : public DeployableObject
{
public:
	Crop(string name, Vector2 size, short progress, short quality) 
		:DeployableObject(DeployableObject::Type::CROP, name, size),
		_progress(progress), _quality(quality)
	{}
	~Crop() {}


	void Update();

	virtual void Interaction() override;

	void Watering() {}
	
	void SetPeriod(short period) { _period = period; }
	void SetProgress(short progress) { _progress = progress; }
	void SetQuality(short quality) { _quality = quality; }

private:
	short _period;
	short _progress;
	short _quality;

};

