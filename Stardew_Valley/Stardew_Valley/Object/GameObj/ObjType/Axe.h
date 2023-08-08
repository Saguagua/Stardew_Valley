#pragma once
class Axe :public GameObject
{
public:
	Axe(int objCode, int frameCode, short cost, short damage)
		:GameObject(objCode, frameCode, 1, 1), _cost(cost), _damage(damage)
	{
		_type = ObjectInfo::Type::AXE;
	}
	// GameObject��(��) ���� ��ӵ�
	virtual void KeyInput() override;
private:
	short _cost;
	short _damage;
};

