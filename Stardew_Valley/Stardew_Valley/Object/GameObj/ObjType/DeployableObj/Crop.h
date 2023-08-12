#pragma once
class Crop : public DeployableObject
{
public:
	Crop(string name, Vector2 size) :DeployableObject(DeployableObject::Type::CROP, name, size) {}
	~Crop() {}


	void Update();

	virtual void Interaction() override;
	virtual void Spawn(string name, shared_ptr<SpawnInfo> data) override;

	void Watering() {}
	
	void SetPeriod(short period) { _period = period; }
	void SetProgress(short progress) { _progress = progress; }
	void SetQuality(short quality) { _quality = quality; }

private:
	short _period;
	short _progress;
	short _quality;

};

