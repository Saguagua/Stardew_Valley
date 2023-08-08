#pragma once
class WateringCan: public GameObject
{
public:
	WateringCan(int objCode, int frameIndex, short maxCount, short count)
		:GameObject(objCode, frameIndex, maxCount, count) 
	{
		_type = ObjectInfo::Type::WATERINGCAN;
	}
	// GameObject을(를) 통해 상속됨
	virtual void KeyInput() override;
};

