#pragma once
class Hoe :public GameObject
{
public:
	Hoe(int objCode, int frameIndex, short maxCount, short count)
		:GameObject(objCode, frameIndex, maxCount, count) 
	{
		_type = ObjectInfo::Type::HOE;
	}
	// GameObject��(��) ���� ��ӵ�
	virtual void KeyInput() override;
};

