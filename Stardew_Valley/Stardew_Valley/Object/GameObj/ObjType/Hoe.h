#pragma once
class Hoe :public GameObject
{
public:
	Hoe(int objCode, int frameIndex, short maxCount, short count)
		:GameObject(objCode, frameIndex, maxCount, count) 
	{
		_type = ObjectInfo::Type::HOE;
	}
	// GameObject을(를) 통해 상속됨
	virtual void KeyInput() override;
};

