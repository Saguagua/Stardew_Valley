#pragma once
class WateringCan: public GameObject
{
public:
	WateringCan(int objCode, int frameIndex, short maxCount, short count)
		:GameObject(objCode, frameIndex, maxCount, count) 
	{
		_type = ObjectInfo::Type::WATERINGCAN;
	}
	// GameObject��(��) ���� ��ӵ�
	virtual void KeyInput() override;
};

