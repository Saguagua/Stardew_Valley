#pragma once
class FishingRod:public GameObject
{
public:
	FishingRod(int itemCode, int frameIndex, short maxCount, short count)
		:GameObject(itemCode, frameIndex, maxCount, count) {
		_type = ObjectInfo::Type::FISHINGROD;
	}
	virtual void Interaction() override;
private:
};

