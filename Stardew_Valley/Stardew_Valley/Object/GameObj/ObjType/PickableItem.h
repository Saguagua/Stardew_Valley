#pragma once
class PickableItem :public GameObject
{
public:
	PickableItem(int objCode, int frameCode, int pickCode, short maxCount)
		:GameObject(objCode, frameCode, maxCount, 1), _pickCode(pickCode) 
	{
		_type = ObjectInfo::Type::PICKABLE;
	}
	virtual ~PickableItem() {}
	virtual void Interaction() override;
private:
	int _pickCode;
};

